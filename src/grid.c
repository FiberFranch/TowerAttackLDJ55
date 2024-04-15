#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <math.h>
#include "grid.h"
#include "raymath.h"

Grid CreateGrid(unsigned int width, unsigned int height) {
    Grid grid;
    grid.width = width;
    grid.height = height;
    grid.grid = (GridTile*) calloc(width * height, sizeof(GridTile));
    return grid;
}

void DestroyGrid(Grid* grid) {
    GridTile* ptr = grid->grid;
    free(ptr);
}

void SetGridTile(const Grid* grid, unsigned int i, unsigned int j, GridTile tile) {
    grid->grid[i + j * grid->width] = tile;
}

GridTile* GetTileFromGrid(const Grid* grid, unsigned int i, unsigned int j) {
    return &grid->grid[i + j * grid->width];
}

Grid LoadGrid(const char *filename) {
    Image image = LoadImage(filename);
    Color *pixels = LoadImageColors(image);
    unsigned int width = image.width;
    unsigned int height = image.height;

    Grid grid = CreateGrid(width, height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = pixels[j * width + i];
            GridTile tile = {0};
            tile.grid_x = i;
            tile.grid_y = j;
            tile.type = DEFAULT_TILE;

            if (pixel.b == 100) {
                tile.type = PATH_TILE;
            }
            if (pixel.b == 200) {
                tile.type = START_TILE;
            }
            if (pixel.b == 255) {
                tile.type = END_TILE;
            }
            if (pixel.r == 255) {
                tile.type = SUMMONER_TILE;
            }
            SetGridTile(&grid, i, j, tile);
        }
    }
    UnloadImageColors(pixels);
    UnloadImage(image);
    return grid;
}

void GetTileFromPosition(int* tile_x, int* tile_y, const Grid* grid,
                         Vector2 position, Vector2 map_size) {
    float tile_width = map_size.x / grid->width;
    float tile_height = map_size.y / grid->height;
    Vector2 origin_offset = (Vector2) {0.5f * map_size.x, 0.5f * map_size.y};
    Vector2 relative = Vector2Add(position, origin_offset);
    *tile_x = (int)floor(relative.x / tile_width);
    *tile_y = (int)floor(relative.y / tile_height);
}

Path CreatePathFromGrid(const Grid* grid) {
    // Look for start and end
    int start_i, start_j, end_i, end_j;
    for (unsigned int i=0; i < grid->width; i++) {
        for (unsigned int j=0; j < grid->height; j++) {
            if (GetTileFromGrid(grid, i, j)->type == START_TILE) {
                start_i = i;
                start_j = j;
            }
            else if (GetTileFromGrid(grid, i, j)->type == END_TILE) {
                end_i = i;
                end_j = j;
            }
        }
    }
    Path path = {0};
    path.tiles = calloc(grid->width * grid->height, sizeof(PathTile));
    int pathLength = 0;
    int current_i = start_i;
    int current_j = start_j;
    PathTile tile;
    bool next_tile_found;
    while (!((current_i == end_i) && (current_j == end_j))) {
        //Add tile found to path
        tile.grid_x = current_i;
        tile.grid_y = current_j;
        path.tiles[pathLength] = tile;
        pathLength++;

        next_tile_found = false;

        // Look at neighbours
        for (int x=-1; x <= 1; x++) {
            if (next_tile_found) break;
            for (int y=-1; y <= 1; y++) {
                if (abs(x) == abs(y)) continue;

                // Check bounds
                if (current_i + x < 0 || current_i + x >= grid->width ||
                    current_j + y < 0 || current_j + y >= grid->height) continue;

                //Skip previous found tile
                if (pathLength >= 2 &&
                    current_i + x == path.tiles[pathLength - 2].grid_x &&
                    current_j + y == path.tiles[pathLength - 2].grid_y) continue;

                if (GetTileFromGrid(grid, current_i + x, current_j + y)->type == PATH_TILE ||
                    GetTileFromGrid(grid, current_i + x, current_j + y)->type == END_TILE) {
                    current_i += x;
                    current_j += y;
                    next_tile_found = true;
                    break;
                }
            }
        }
        if (! next_tile_found) {
           printf("ERROR::CreatePathFromGrid: The path does not connect with the end Tile\n");
           break;
        }
    }
    //Add last tile
    if (current_i == end_i && current_j == end_j) {
        tile.grid_x = current_i;
        tile.grid_y = current_j;
        path.tiles[pathLength] = tile;
        pathLength++;
        path.size = pathLength;
    } else {
        printf("ERROR::CreatePathFromGrid: The path does not connect with the end Tile\n");
    }
    return path;
}

Vector2 GetWorldPositionFromGrid(const Grid* grid, Vector2 dimensions, int i, int j) {
    float scalex = dimensions.x / grid->width;
    float scaley = dimensions.y / grid->height;
    Vector2 position = { scalex * (i + 0.5f), scaley * (j + 0.5f)};
    Vector2 offset = (Vector2){0.5f*dimensions.x, 0.5f*dimensions.y};
    return Vector2Subtract(position, offset);
}

Vector2 GetTileTypeWorldPosition(const Grid* grid, Vector2 dimensions, TILE_TYPE type) {
    for (unsigned int i = 0; i < grid->width; i++) {
        for (unsigned int j = 0; j < grid->height; j++) {
            if (GetTileFromGrid(grid, i, j)->type == type) {
                return GetWorldPositionFromGrid(grid, dimensions, i, j);
            }
        }
    }
    return (Vector2){0};
}

PathSampler CreatePathSampler(Grid* grid, Path path, Vector2 dimensions) {
    PathSampler sampler;
    sampler.references = calloc(path.size, sizeof(Vector2));
    sampler.distances = calloc(path.size, sizeof(float));
    sampler.n_references = 1;

    float tile_width = dimensions.x / grid->width;
    float tile_height = dimensions.y / grid->height;
    int path_x = path.tiles[0].grid_x;
    int path_y = path.tiles[0].grid_y;
    sampler.references[0] = GetWorldPositionFromGrid(grid, dimensions, path_x, path_y);

    float total_distance = 0.0f;
    for (int i = 1; i < path.size; i++) {
        int path_new_x = path.tiles[i].grid_x;
        int path_new_y = path.tiles[i].grid_y;
        if ((path_new_x != path_x) || (path_new_y != path_y)) {
            Vector2 direction = Vector2Normalize((Vector2){path_new_x - path_x, path_new_y - path_y});
            int index = sampler.n_references;
            sampler.references[index] = GetWorldPositionFromGrid(grid, dimensions, path_new_x, path_new_y);
            float segment_distance = Vector2Distance(sampler.references[index], sampler.references[index-1]);
            total_distance += segment_distance;
            sampler.distances[index-1] = segment_distance;
            sampler.n_references++;
        }
    }
    for (int i = 0; i < sampler.n_references-1; i++) {
        sampler.distances[i] /= total_distance;
    }
    sampler.total_distance = total_distance;
    return sampler;
}

Vector2 SamplePath(PathSampler sampler, float s) {
    if (s > 1.0f) {
        printf("s = %f\n", s);
        return sampler.references[sampler.n_references-1];
    }

    float cumulated_distance = 0.0;
    float last_distance = 0.0;
    for (int i = 0; i < sampler.n_references-1; i++) {
        cumulated_distance += sampler.distances[i];
        if (s < cumulated_distance) {
            Vector2 A = sampler.references[i];
            Vector2 B = sampler.references[i+1];
            float interpolation_value = (s - last_distance) / sampler.distances[i];
            float a = (1.0f - interpolation_value);
            float b = interpolation_value;
            Vector2 point = Vector2Add((Vector2){a*A.x, a*A.y}, (Vector2){b*B.x, b*B.y} );
            return point;
        }
        last_distance = cumulated_distance;}
    return sampler.references[sampler.n_references-1];
}


void DestroyPathSampler(PathSampler sampler) {
    free(sampler.references);
    free(sampler.distances);
}

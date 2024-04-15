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
            GridTile tile;
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
    Vector2 relative = Vector2Subtract(position, origin_offset);
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
    printf("start: %d %d\nend: %d %d\n", start_i, start_j, end_i, end_j);
    printf("grid size: %d %d\n", grid->width, grid->width);
    Path path = {0};
    path.tiles = calloc(grid->width * grid->height, sizeof(PathTile));
    int pathLength = 0;
    int current_i = start_i;
    int current_j = start_j;
    PathTile tile;
    bool next_tile_found;
    while (current_i != end_i && current_j != end_j) {
    //while (current_i != end_i && current_j != end_j && pathLength < grid->width * grid->height) {
    //while (current_i != end_i && current_j != end_j && pathLength < 5) {
        //Add tile found to path
        tile.grid_x = current_i;
        tile.grid_y = current_j;
        path.tiles[pathLength] = tile;
        pathLength++;

        next_tile_found = false;
        // Look at neighbours

        printf("ROUND %d\n", pathLength);

        for (int x=-1; x <= 1; x++) {
            for (int y=-1; y <= 1; y++) {
                if (abs(x) == abs(y)) continue;
                printf ("x y: %d %d\n", x, y);

                if (GetTileFromGrid(grid, current_i + x, current_j + y)->type == PATH_TILE ||
                    GetTileFromGrid(grid, current_i + x, current_j + y)->type == END_TILE) {
                    printf("current coordinates: %d %d\n", path.tiles[pathLength - 1].grid_x, path.tiles[pathLength - 1].grid_y);
                    printf("possible next coordinates: %d %d\n", current_i + x, current_j + y);
                    if (pathLength > 1)printf("last coordinates: %d %d\n", path.tiles[pathLength - 2].grid_x, path.tiles[pathLength - 2].grid_y);
                }

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
            if (next_tile_found) break;
        }
        if (! next_tile_found) {
            printf("ERROR::CreatePathFromGrid: The path does not connect with the end Tile\n");
            break;
        }
        printf("\n--------------------------------\n\n");
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

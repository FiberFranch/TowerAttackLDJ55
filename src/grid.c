#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "grid.h"

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

Grid LoadGrid(char *filename) {
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
    path.tiles = calloc(200, sizeof(PathTile));
    int pathLength = 0;
    int current_i = start_i;
    int current_j = start_j;
    while (current_i != end_i && current_j != end_j) {
        int iteration_i = current_i;
        int iteration_j = current_j;
        PathTile tile;
        tile.grid_x = current_i;
        tile.grid_y = current_j;
        path.tiles[pathLength] = tile;
        pathLength++;

        // Look at neighbours
        for (int x=-1; x <= 1; x++) {
            for (int y=-1; y <= 1; y++) {
                if (abs(x) == abs(y)) continue;
                // Check bounds
                if (current_i + x < 0 || current_i + x >= grid->width ||
                    current_j + y < 0 || current_j + y >= grid->height) continue;

                // Avoid last path tile
                if (tile.grid_x == current_i + x && tile.grid_y == current_j + y) continue;

                if (GetTileFromGrid(grid, current_i, current_j)->type == PATH_TILE ||
                    GetTileFromGrid(grid, current_i, current_j)->type == END_TILE) {
                    current_i += x;
                    current_j += y;
                }
            }
        }
        if (iteration_i == current_i && iteration_j == current_j) {
            printf("ERROR::CreatePathFromGrid: The path does not connect with the end Tile\n");
            break;
        }
    }
    return path;
}

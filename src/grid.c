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
                tile.type = OBSTACLE_TILE;
            }
            SetGridTile(&grid, i, j, tile);
        }
    }
    UnloadImageColors(pixels);
    UnloadImage(image);
    return grid;
}

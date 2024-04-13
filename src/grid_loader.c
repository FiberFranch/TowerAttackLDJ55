#include <stdio.h>
#include "raylib.h"
#include "grid.h"

Grid loadGrid(char *filename) {
    Image image = LoadImage(filename);
    Color *pixels = LoadImageColors(image);
    unsigned int width = image.width;
    unsigned int height = image.height;

    Grid grid = CreateGrid(width, height);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color pixel = pixels[j * width + i];

            if (pixel.b == 100)
                SetGridTile(&grid, i, j, PATH_TILE);

            if (pixel.b == 200)
                SetGridTile(&grid, i, j, OBSTACLE_TILE);
        }
    }

    return grid;
}

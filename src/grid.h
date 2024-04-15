#ifndef GRID_H_
#define GRID_H_

#include "raymath.h"
#include <raylib.h>
#include <stdlib.h>
typedef enum {
PATH_TILE,
DEFAULT_TILE,
START_TILE,
END_TILE,
SUMMONER_TILE,
} TILE_TYPE;

typedef struct {
    TILE_TYPE type;
    bool occupied;
    int grid_x, grid_y;
} GridTile;

typedef struct {
    GridTile* grid;
    unsigned int width, height;
} Grid;

Grid CreateGrid(unsigned int width, unsigned int height);

void DestroyGrid(Grid* grid);

void SetGridTile(const Grid* grid, unsigned int i, unsigned int j, GridTile tile);

GridTile* GetTileFromGrid(const Grid* grid, unsigned int i, unsigned int j);

Grid LoadGrid(const char* filename);

void GetTileFromPosition(int* tile_x, int* tile_y, const Grid* grid,
                         Vector2 position, Vector2 map_size);
typedef struct {
    int grid_x, grid_y;
} PathTile;

typedef struct {
    PathTile* tiles;
    int size;
} Path;

Path CreatePathFromGrid(const Grid* grid);

Vector2 GetWorldPositionFromGrid(const Grid* grid, Vector2 dimensions, int i, int j);

Vector2 GetTileTypeWorldPosition(const Grid* grid, Vector2 dimensions, TILE_TYPE type);

typedef struct {
    Vector2* references;
    float* distances;
    float total_distance;
    int n_references;
} PathSampler;


PathSampler CreatePathSampler(Grid* grid, Path path, Vector2 dimensions);

Vector2 SamplePath(PathSampler sampler, float s);

void DestroyPathSampler(PathSampler sampler);

#endif // GRID_H_

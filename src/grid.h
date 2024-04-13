#ifndef GRID_H_
#define GRID_H_

typedef enum {
PATH_TILE,
OBSTACLE_TILE,
} TILE_TYPE;

typedef struct {
    TILE_TYPE type;
} GridTile;

typedef struct {
    GridTile* grid;
    unsigned int width, height;
} Grid;

Grid CreateGrid(unsigned int width, unsigned int height);

void DestroyGrid(Grid* grid);

void SetGridTile(const Grid* grid, unsigned int i, unsigned int j, GridTile* tile);

GridTile* GetTileFromGrid(const Grid* grid, unsigned int i, unsigned int j);

#endif // GRID_H_
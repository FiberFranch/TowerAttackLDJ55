#ifndef GRID_H_
#define GRID_H_

typedef enum {
PATH_TILE,
OBSTACLE_TILE,
DEFAULT_TILE,
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

void SetGridTile(const Grid* grid, unsigned int i, unsigned int j, GridTile tile);

GridTile* GetTileFromGrid(const Grid* grid, unsigned int i, unsigned int j);

Grid LoadGrid(char* filename);

void GetTileFromPosition(int* tile_x, int* tile_y, const Grid* grid,
        Vector2 position, Vector2 map_size, Vector2 origin_offset);

#endif // GRID_H_

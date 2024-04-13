#ifndef ASSET_LOADER_H_
#define ASSET_LOADER_H_

#include <raylib.h>

// Set sprite names here
// Sprites should be png images placed inside the assets/ directory
#define LIST_OF_SPRITES \
    SPRITE(map_test) \
    SPRITE(heightmap)

// Mehses should be obj files placed inside the assets/ directory
#define LIST_OF_MODELS \
    MODEL(plane) \
    MODEL(rectangle)

typedef enum {
#define SPRITE(name) SPRITE_ID_##name,
LIST_OF_SPRITES
#undef SPRITE
} SPRITE_ID;

typedef enum {
#define MODEL(name) MODEL_ID_##name,
LIST_OF_MODELS
#undef MODEL
} MODEL_ID;

void LoadAllAssets();

void UnloadAllAssets();

void ReloadAllAssets();

Image* GetSpriteByID(SPRITE_ID id);

Texture2D* GetTextureByID(SPRITE_ID id);

Model* GetModelByID(MODEL_ID id);

#endif // ASSET_LOADER_H_

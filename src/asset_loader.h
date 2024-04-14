#ifndef ASSET_LOADER_H_
#define ASSET_LOADER_H_

#include <raylib.h>

// Set sprite names here
// Sprites should be png images placed inside the assets/ directory
#define LIST_OF_SPRITES \
    SPRITE(path) \
    SPRITE(summoner) \
    SPRITE(bishop) \
    SPRITE(default) \
    SPRITE(plant) \
    SPRITE(map_test) \
    SPRITE(heightmap)

// Mehses should be obj files placed inside the assets/ directory
#define LIST_OF_MODELS \
    MODEL(plane) \
    MODEL(rectangle)

#define LIST_OF_SHADERS \
    SHADER(map) \
    SHADER(lookup) \
    SHADER(lighting)

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

typedef enum {
#define SHADER(name) SHADER_ID_##name,
LIST_OF_SHADERS
#undef SHADER
} SHADER_ID;

void LoadAllAssets();

void UnloadAllAssets();

Image* GetSpriteById(SPRITE_ID id);

Texture2D* GetTextureById(SPRITE_ID id);

Model* GetModelById(MODEL_ID id);

Shader* GetShaderById(SHADER_ID id);

#endif // ASSET_LOADER_H_

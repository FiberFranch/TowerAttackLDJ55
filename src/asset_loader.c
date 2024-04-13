#include <raylib.h>
#include <stdlib.h>

#include "asset_loader.h"

Texture* textures;
Image* sprites;
Model* models;

#define SPRITE(name) "assets/"#name".png",
char* SpriteFileNames[] = {
LIST_OF_SPRITES
};
#undef SPRITE

#define MODEL(name) "assets/"#name".obj",
char* ModelFileNames[] = {
LIST_OF_MODELS
};
#undef MODEL

void LoadAllAssets() {
    // Sprites & textures
    const unsigned int N_SPRITES = sizeof(SpriteFileNames) / sizeof(char*);
    sprites = calloc(N_SPRITES, sizeof(Image));
    textures = calloc(N_SPRITES, sizeof(Texture2D));
    for (unsigned int i = 0; i < N_SPRITES; i++) {
        sprites[i] = LoadImage(SpriteFileNames[i]);
        textures[i] = LoadTextureFromImage(sprites[i]);
    }

    // Models
    const unsigned int N_MODELS = sizeof(ModelFileNames) / sizeof(char*);
    models = calloc(N_MODELS, sizeof(Model));
    for (unsigned int i = 0; i < N_MODELS; i++) {
        models[i] = LoadModel(ModelFileNames[i]);
    }
}

void UnloadAllAssets() {
    // Sprites && Textures
    const unsigned int N_SPRITES = sizeof(SpriteFileNames) / sizeof(char*);
    for (unsigned int i = 0; i < N_SPRITES; i++) {
        UnloadImage(sprites[i]);
        UnloadTexture(textures[i]);
    }
    free(sprites);
    free(textures);

    const unsigned int N_MODELS = sizeof(ModelFileNames) / sizeof(char*);
    for (unsigned int i = 0; i < N_MODELS; i++) {
        UnloadModel(models[i]);
    }
    free(models);
}

void ReloadAllAssets() {
    UnloadAllAssets();
    LoadAllAssets();
}

Image* GetSpriteByID(SPRITE_ID id) {
    return &sprites[id];
}

Texture2D* GetTextureByID(SPRITE_ID id) {
    return &textures[id];
}

Model* GetModelByID(MODEL_ID id) {
    return &models[id];
}

#include <raylib.h>
#include <stdlib.h>

#include "asset_loader.h"

Texture* textures;
Image* sprites;
Model* models;
Shader* shaders;

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

#define SHADER(name) "assets/shaders/"#name".fs",
char* FragmentShaderNames[] = {
LIST_OF_SHADERS
};
#undef SHADER

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

    // Shaders
    const unsigned int N_SHADERS = sizeof(FragmentShaderNames) / sizeof(char*);
    shaders = calloc(N_SHADERS, sizeof(Shader));
    for (unsigned int i = 0; i < N_SHADERS; i++) {
        shaders[i] = LoadShader("assets/shaders/default.vs", FragmentShaderNames[i]);
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

    const unsigned int N_SHADERS = sizeof(FragmentShaderNames) / sizeof(char*);
    for (unsigned int i = 0; i < N_SHADERS; i++) {
        UnloadShader(shaders[i]);
    }
    free(shaders);
}

Image* GetSpriteById(SPRITE_ID id) {
    return &sprites[id];
}

Texture2D* GetTextureById(SPRITE_ID id) {
    return &textures[id];
}

Model* GetModelById(MODEL_ID id) {
    return &models[id];
}

Shader* GetShaderById(SHADER_ID id) {
    return &shaders[id];
}

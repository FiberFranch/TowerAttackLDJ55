#include <raylib.h>
#include <stdlib.h>

#include "asset_loader.h"

Image* sprites;

#define SPRITE(name) "assets/"#name".png",
char* SpriteFileNames[] = {
LIST_OF_SPRITES
};
#undef SPRITE

void LoadAllAssets() {
    // Sprites
    const unsigned int N_SPRITES = sizeof(SpriteFileNames) / sizeof(char*);
    sprites = calloc(N_SPRITES, sizeof(Image));
    for (unsigned int i = 0; i < N_SPRITES; i++) {
        sprites[i] = LoadImage(SpriteFileNames[i]);
    }
}

void UnloadAllAssets() {
    // Sprites
    const unsigned int N_SPRITES = sizeof(SpriteFileNames) / sizeof(char*);
    for (unsigned int i = 0; i < N_SPRITES; i++) {
        UnloadImage(sprites[i]); // Delete each image at a time
    }
    free(sprites);
}

Image GetSpriteByID(SPRITE_ID id) {
    return sprites[id];
}

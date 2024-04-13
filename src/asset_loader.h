#ifndef ASSET_LOADER_H_
#define ASSET_LOADER_H_

#include <raylib.h>

// Set sprite names here
// Sprites should be png images placed inside the assets/ directory
#define LIST_OF_SPRITES \
    SPRITE(enemy1) \
    SPRITE(tower1) \
    SPRITE(tower2) \
    SPRITE(summoner)

typedef enum {
#define SPRITE(name) name,
LIST_OF_SPRITES
#undef SPRITE
} SPRITE_ID;

void LoadAllAssets();

void UnloadAllAssets();

Image GetSpriteByID(SPRITE_ID id);

#endif // ASSET_LOADER_H_

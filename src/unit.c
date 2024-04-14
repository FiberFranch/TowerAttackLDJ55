#include <string.h>
#include <raylib.h>
#include "unit.h"
#include "asset_loader.h"

Enemy CreateEnemy(Image* sprite, const int hitpoints, const int damage, const int speed) {
    Enemy enemy;
    enemy.sprite = sprite;
    enemy.hitpoints = hitpoints;
    enemy.damage = damage;
    enemy.speed = speed;

    return enemy;
}

Enemy GetEnemyById(const char* name) {
    Enemy enemy;
    if (strcmp(name, "monster1")){
        enemy.sprite = GetSpriteById(SPRITE_ID_map_test);
        enemy.hitpoints = 30;
        enemy.damage = 100;
        enemy.speed = 2;
    }

    return enemy;
}

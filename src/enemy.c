#include <string.h>
#include "raylib.h"
#include "enemy.h"
#include "asset_loader.h"

Enemy CreateEnemy(const Image* sprite, const int hitpoints, const int damage, const int speed) {
    Enemy enemy;
    enemy.sprite = sprite;
    enemy.hitpoints = hitpoints;
    enemy.damage = damage;
    enemy.speed = speed;

    return enemy;
}

Enemy GetEnemyById(const char* name) {
    Enemy enemy;
    if (strcmp(enemy, "monster1")){
        enemy.sprite = GetSpriteById("Monster1Sprite");
        enemy.hitpoints = 30;
        enemy.damage = 100;
        enemy.speed = 2;
    }

    return enemy;
}

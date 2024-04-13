#include "raylib.h"
#include "enemy.h"

Enemy CreateEnemy(const Image* sprite, const int hitpoints, const int damage, const int speed) {
    Enemy enemy;
    enemy.sprite = sprite;
    enemy.hitpoints = hitpoints;
    enemy.damage = damage;
    enemy.speed = speed;

    return enemy;
}

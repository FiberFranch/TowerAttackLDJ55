#ifndef ENEMY_H_
#define ENEMY_H_

#include "raylib.h"

typedef struct { 
    Image* sprite;
    int hitpoints;
    int damage;
    int speed;
    int pos_x;
    int pos_y;
} Enemy;

Enemy CreateEnemy(const Image* sprite, const int hitpoints, const int damage, const int speed);

#endif // ENEMY_H_

#ifndef UNIT_H_
#define UNIT_H_

#include "raylib.h"

typedef enum {
PROJECTILE,
FLAMES,
} Ability;

typedef enum {
FACE_UP,
FACE_DOWN,
FACE_LEFT,
FACE_RIGHT,
} SummonOrientation;

typedef struct {
    float Cooldown;
    int grid_x, grid_y;
    SummonOrientation orientation;
    Ability ability;
} Summon;

typedef struct {
    int hitpoints;
    int mana;
    int n_summons;
    Vector2 position;
    Summon* summons;
} Summoner;

typedef struct { 
    Image* sprite;
    int hitpoints;
    int damage;
    int speed;
    int pos_x,pos_y;
} Enemy;

Enemy CreateEnemy(Image* sprite, const int hitpoints, const int damage, const int speed);

Enemy GetEnemyById(const char* name);

#endif // UNIT_H_

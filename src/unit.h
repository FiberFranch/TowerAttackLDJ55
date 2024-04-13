#ifndef UNIT_H_
#define UNIT_H_

#include "raylib.h"

typedef struct {
    char* ID;
    Image* Sprite;
} Ability;

typedef struct {
    float Cooldown;
} Summon;

typedef struct {
    int hitpoints;
    int mana;
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

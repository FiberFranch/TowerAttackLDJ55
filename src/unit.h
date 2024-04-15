#ifndef UNIT_H_
#define UNIT_H_

#include <raylib.h>

typedef enum {
PROJECTILE,
FLAMES,
WHIRL,
} Ability;

typedef enum {
FACE_UP,
FACE_DOWN,
FACE_LEFT,
FACE_RIGHT,
} SummonOrientation;

typedef struct {
    Texture2D* sprite;
    float max_cooldown, cooldown_timer;
    int damage;
    int grid_x, grid_y;
    SummonOrientation orientation;
    Ability ability;
} Summon;

typedef struct {

} SummonedList;

typedef struct {
    int hitpoints, mana;
    int n_summons;
    Vector2 position;
    Summon* summons;
} Summoner;

typedef struct { 
    Texture2D* sprite;
    int hitpoints;
    int damage;
    float speed;
    Vector2 position;
    float s;
} Enemy;

Enemy CreateEnemy(Texture2D* sprite, const int hitpoints, const int damage, const int speed);

Enemy GetEnemyById(const char* name);

void DrawEnemy(const Enemy* enemy, float scale, int number);

void DrawSummoner(float scale, Vector2 position);f (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))

void DrawSummon(const Summon* summon, float scale);

Summon CreateSummonEvaristo();

#endif // UNIT_H_

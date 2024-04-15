#include <math.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "unit.h"
#include "asset_loader.h"
#include "raymath.h"
#include "render.h"

Enemy CreateEnemy(Texture2D* sprite, const int hitpoints, const int damage, const int speed) {
    Enemy enemy;
    enemy.sprite = sprite;
    enemy.hitpoints = hitpoints;
    enemy.damage = damage;
    enemy.speed = speed;
    enemy.s =0.0f;
    return enemy;
}

Enemy GetEnemyById(const char* name) {
    Enemy enemy;
    if (strcmp(name, "bishop ")){
        enemy.sprite = GetTextureById(SPRITE_ID_bishop);
        enemy.hitpoints = 1;
        enemy.damage = 100;
        enemy.speed = 1.0f;
        enemy.position = (Vector2){0};
        enemy.s = 0.0f;
    }

    return enemy;
}

void DrawSummoner(float scale, Vector2 position) {
    Model summoner = *GetModelById(MODEL_ID_rectangle);
    summoner.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *GetTextureById(SPRITE_ID_summoner);
    DrawModel(summoner, (Vector3){position.x, 0.05 * (sin(GetTime()) + 2.0), position.y}, 2.0f/scale, WHITE);
}

Summon CreateSummonEvaristo() {
    Summon Evaristo;
    Evaristo.max_cooldown = 2.f;
    Evaristo.cooldown_timer = 2.f;
    Evaristo.damage = 10;
    Evaristo.orientation = FACE_DOWN;
    Evaristo.ability = PROJECTILE;
    Evaristo.sprite = GetTextureById(SPRITE_ID_evaristo);
    return Evaristo;
}

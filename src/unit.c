#include <math.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "unit.h"
#include "asset_loader.h"
#include "raymath.h"

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
        enemy.hitpoints = 30;
        enemy.damage = 100;
        enemy.speed = 1.0f;
        enemy.position = (Vector2){0};
        enemy.s = 0.0f;
    }

    return enemy;
}

void DrawEnemy(const Enemy* enemy, float scale, int number) {
    Model model = *GetModelById(MODEL_ID_rectangle);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(enemy->sprite);
    float displacement = 0.03f * (sin(5.0f * GetTime()) + 1.0f);
    float rotation = 2.0f * sin(5.0f*GetTime() + 5.0f * number);
    DrawModelEx(model, (Vector3){enemy->position.x, displacement, enemy->position.y},
                (Vector3){0.0f, 0.0f, 1.0f}, rotation, (Vector3){1.0f / scale, 1.0f / scale, 1.0f / scale}, WHITE);
}

void DrawSummoner(float scale, Vector2 position) {
    Model summoner = *GetModelById(MODEL_ID_rectangle);
    summoner.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *GetTextureById(SPRITE_ID_summoner);
    DrawModel(summoner, (Vector3){position.x, 0.05 * (sin(GetTime()) + 2.0), position.y}, 2.0f/scale, WHITE);
}

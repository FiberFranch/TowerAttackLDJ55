#include <math.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "unit.h"
#include "asset_loader.h"

Enemy CreateEnemy(Texture2D* sprite, const int hitpoints, const int damage, const int speed) {
    Enemy enemy;
    enemy.sprite = sprite;
    enemy.hitpoints = hitpoints;
    enemy.damage = damage;
    enemy.speed = speed;

    return enemy;
}

Enemy GetEnemyById(const char* name) {
    Enemy enemy;
    if (strcmp(name, "bishop ")){
        enemy.sprite = GetTextureById(SPRITE_ID_bishop);
        enemy.hitpoints = 30;
        enemy.damage = 100;
        enemy.speed = 2;
        enemy.position = (Vector2){0};
    }

    return enemy;
}

void DrawEnemy(const Enemy* enemy, float scale) {
    Model model = *GetModelById(MODEL_ID_rectangle);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *(enemy->sprite);
    DrawModel(model, (Vector3){enemy->position.x, 0.0f, enemy->position.y}, 1.0f / scale, WHITE);
    /* DrawModel(model, (Vector3){0.0f, 0.0f, 0.0f}, 1.0f, WHITE); */
}

void DrawSummoner(float scale, Vector2 position) {
    Model summoner = *GetModelById(MODEL_ID_rectangle);
    summoner.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = *GetTextureById(SPRITE_ID_summoner);
    DrawModel(summoner, (Vector3){position.x, 0.05 * (sin(GetTime()) + 2.0), position.y}, 2.0f/scale, WHITE);
}

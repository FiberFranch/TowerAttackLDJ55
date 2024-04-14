#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit.h"
#include "level.h"
#include "grid.h"

EnemyQueue LoadEnemyQueue(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening enemy list\n");
        exit(1);
    }

    int capacity = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            capacity++;
        }
    }
    fclose(file);

    file = fopen(filename, "r");
    EnemyQueue queue;
    queue.capacity = capacity;
    queue.next_enemy = 0;
    queue.enemy_spawns = (EnemySpawn*) calloc(queue.capacity, sizeof(EnemySpawn));

    char enemy[100];
    float time;
    int i = 0;
    while (fscanf(file, "%s %f", enemy, &time) == 2) {
        queue.enemy_spawns[i].enemy = GetEnemyById(enemy);
        queue.enemy_spawns[i].time = time;
        i++;
    }
    fclose(file);

    return queue;
}

void DeleteEnemyQueue(EnemyQueue* queue) {
    EnemySpawn* ptr = queue->enemy_spawns;
    free(ptr);
}

void EnemyQueueSetStartingPosition(EnemyQueue* queue, Vector2 position) {
    for (unsigned int i = 0; i < queue->capacity; i++) {
        queue->enemy_spawns->enemy.position = position;
    }
}

Enemy* GetNextEnemy(EnemyQueue* queue, float time) {
    if (queue->next_enemy >= queue->capacity) return NULL; // Avoid memory issues when running out of enemies
    EnemySpawn* enemy_spawn = &queue->enemy_spawns[queue->next_enemy];
    /* printf("spawn time = %f\n", enemy_spawn->time); */
    if (enemy_spawn->time <= time) {
        queue->next_enemy++;
        return &(enemy_spawn->enemy);
    }
    return NULL;
}

EnemyList CreateEnemyList(const unsigned int capacity) {
    EnemyList list;
    list.capacity = capacity;
    list.last_enemy = 0;
    list.enemies = (Enemy*) calloc(list.capacity, sizeof(Enemy));
    return list;
}

void DeleteEnemyList(EnemyList* list) {
    Enemy* ptr = list->enemies;
    free(ptr);
}

void AddEnemyToEnemyList(EnemyList* list, Enemy enemy) {
    list->enemies[list->last_enemy] = enemy;
    list->last_enemy++;
}

void RemoveEnemyFromEnemyList(EnemyList* list, int index) {
    for (int i = index; i < list->last_enemy - 1; i++) {
        list->enemies[i] = list->enemies[i+1];
    }
    list->last_enemy--;
}

SummonList CreateSummonList(const unsigned int capacity) {
    SummonList list;
    list.capacity = capacity;
    list.last_summon = 0;
    list.summons = (Summon*) calloc(list.capacity, sizeof(Summon));
    return list;
}

void DeleteSummonList(SummonList* list) {
    Summon* ptr = list->summons;
    free(ptr);
}

void AddSummonToSummonList(SummonList* list, Summon summon) {
    list->summons[list->last_summon] = summon;
    list->last_summon++;
}

OccupationGrid CreateOccupationGrid(int width, int height) {
    OccupationGrid grid;
    grid.width = width;
    grid.height = height;
    grid.occupied = (bool*) calloc(grid.width * grid.height, sizeof(bool));
    for (int j = 0; j < grid.height; j++) {
        for (int i = 0; i < grid.width; i++)
            grid.occupied[j * grid.width + i] = false;
    }
    return grid;
}

void DeleteOccupationGrid(OccupationGrid* grid) {
    bool* ptr = grid->occupied;
    free(ptr);
}

void UpdateOccupationGrid(const EnemyList* enemies, OccupationGrid* occupation,
                          const Grid* grid, Vector2 map_size) {
    for (int j = 0; j < occupation->height; j++) {
        for (int i = 0; i < occupation->width; i++)
            occupation->occupied[j * occupation->width + i] = false;
    }
    int tile_x, tile_y;
    for (int i = 0; i < enemies->last_enemy; i++) {
        GetTileFromPosition(&tile_x, &tile_y, grid, enemies->enemies[i].position, map_size);
        occupation->occupied[tile_y * occupation->width + tile_x] = true;
    }
}

DamageGrid CreateDamageGrid(int width, int height) {
    DamageGrid grid;
    grid.width = width;
    grid.height = height;
    grid.damage = (int*) calloc(grid.width * grid.height, sizeof(int));
    for (int j = 0; j < grid.height; j++) {
        for (int i = 0; i < grid.width; i++)
            grid.damage[j * grid.width + i] = 0;
    }
    return grid;
}

void DeleteDamageGrid(DamageGrid* grid) {
    int* ptr = grid->damage;
    free(ptr);
}

bool AttemptDealDamage(Summon* summon, const Grid* grid, DamageGrid* damage,
                       const OccupationGrid* occupation, int i, int j) {
    if (occupation->occupied[j * grid->width + i]) {
        damage->damage[j * grid->width + i] += summon->damage;
        summon->cooldown_timer = 0.f;
        return true;
    }
    return false;
}

void ComputeDirectionOffset(SummonOrientation orientation, int* x, int* y) {
    switch(orientation) {
        case FACE_UP:
            *x = 0;
            *y = -1;
            return;
        case FACE_DOWN:
            *x = 0;
            *y = 1;
            return;
        case FACE_LEFT:
            *x = -1;
            *y = 0;
            return;
        case FACE_RIGHT:
            *x = 1;
            *y = 0;
            return;
    }
}

bool AttemptCastAbility(Summon* summon, const Grid* grid,
                        const OccupationGrid* occupation, DamageGrid* damage) {
    bool result = false;
    if (summon->cooldown_timer >= summon->max_cooldown) {
        switch(summon->ability) {
            case PROJECTILE:
            {
                int x, y;
                ComputeDirectionOffset(summon->orientation, &x, &y);
                result = AttemptDealDamage(summon, grid, damage, occupation,
                                           summon->grid_x + x,
                                           summon->grid_y + y);
                break;
            }
            case FLAMES:
            {
                int x, y;
                ComputeDirectionOffset(summon->orientation, &x, &y);
                for (int offset = -1; offset <= 1; offset++) {
                    result = AttemptDealDamage(summon, grid, damage, occupation,
                                               summon->grid_x + x + offset * (-y),
                                               summon->grid_y + y + offset * x) || result;
                }
                break;
            }
            case WHIRL:
            {
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x != 0 && y != 0) {
                            result = AttemptDealDamage(summon, grid, damage, occupation,
                                                       summon->grid_x + x,
                                                       summon->grid_y + y) || result;
                        }
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    return result;
}
void UpdateDamageGrid(SummonList* summons, const OccupationGrid* occupation,
                      DamageGrid* damage, const Grid* grid, Vector2 map_size) {
    for (int j = 0; j < damage->height; j++) {
        for (int i = 0; i < damage->width; i++)
            damage->damage[j * damage->width + i] = 0;
    }
    for (int i = 0; i < summons->last_summon; i++) {
        AttemptCastAbility(&(summons->summons[i]), grid, occupation, damage);
    }
}

void ApplyDamageToEnemies(const DamageGrid* damage_grid, const Grid* grid, Vector2 dimensions, EnemyList* enemy_list) {
    for (unsigned int i = 0; i < enemy_list->last_enemy; i++) {
        Enemy* enemy = &enemy_list->enemies[i];
        int* tile_x;
        int* tile_y;
        GetTileFromPosition(tile_x, tile_y, grid, enemy->position, dimensions);
        int damage = damage_grid->damage[(*tile_x) + grid->width * (*tile_y)];
        enemy->hitpoints -= damage;
        if (enemy->hitpoints <= 0) {
            RemoveEnemyFromEnemyList(enemy_list, i);
        }
    }
}

Level LoadLevel(Summoner summoner, const char* grid_file, const char* enemies_file) {
    Level level;
    level.summoner = summoner;
    level.spawn_queue = LoadEnemyQueue(enemies_file);
    level.grid = LoadGrid(grid_file);
    return level;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit.h"
#include "level.h"
#include "grid.h"

EnemyQueue createEnemyQueue(const char* filename) {
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

    EnemyQueue queue;
    queue.capacity = capacity;
    queue.next_enemy = 0;
    queue.enemy_spawns = (EnemySpawn*) calloc(queue.capacity, sizeof(EnemySpawn));

    char enemy[100];
    int time;
    int i = 0;
    while (fscanf(file, "%s %d", enemy, &time) == 2) {
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

Enemy* GetNextEnemy(EnemyQueue queue, float time) {
    EnemySpawn* enemy_spawn = &queue.enemy_spawns[queue.next_enemy];
    if (enemy_spawn->time >= time) {
        queue.next_enemy++;
    }
    return &(enemy_spawn->enemy);
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
                         Grid* grid, Vector2 map_size, Vector2 origin_offset) {
    for (int j = 0; j < occupation->height; j++) {
        for (int i = 0; i < occupation->width; i++)
            occupation->occupied[j * occupation->width + i] = false;
    }
    int tile_x, tile_y;
    for (int i = 0; i < enemies->last_enemy; i++) {
        GetTileFromPosition(&tile_x, &tile_y, grid,
                         enemies->enemies[i].position,
                         map_size, origin_offset);
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

void AttemptCastAbility(Summon* summon, Grid* grid,
                        const OccupationGrid* occupation, DamageGrid* damage) {
    if (summon->cooldown_timer >= summon->max_cooldown) {
        switch(summon->ability) {
            case PROJECTILE:
                switch(summon->orientation) {
                    case FACE_UP:
                        if (occupation->occupied[(summon->grid_y - 1) *
                                                  grid->width +
                                                  summon->grid_x]) {
                            damage->damage[(summon->grid_y - 1) *
                                             grid->width +
                                             summon->grid_x] +=
                                             summon->damage;
                            summon->cooldown_timer = 0.f;
                        }
                        break;
                    case FACE_DOWN:
                        if (occupation->occupied[(summon->grid_y + 1) *
                                                  grid->width +
                                                  summon->grid_x]) {
                            damage->damage[(summon->grid_y + 1) *
                                            grid->width +
                                            summon->grid_x] +=
                                            summon->damage;
                            summon->cooldown_timer = 0.f;
                        }
                        break;
                    case FACE_LEFT:
                        if (occupation->occupied[(summon->grid_y) *
                                                   grid->width +
                                                  summon->grid_x - 1]) {
                            damage->damage[(summon->grid_y) *
                                            grid->width +
                                            summon->grid_x - 1] +=
                                            summon->damage;
                            summon->cooldown_timer = 0.f;
                        }
                        break;
                    case FACE_RIGHT:
                            if (occupation->occupied[(summon->grid_y) *
                                                      grid->width +
                                                      summon->grid_x + 1]) {
                                damage->damage[(summon->grid_y) *
                                                grid->width +
                                                summon->grid_x + 1] +=
                                                summon->damage;
                                summon->cooldown_timer = 0.f;
                            }
                        break;
                    default:
                        break;
                }
                break;
            case FLAMES:
                switch(summon->orientation) {
                    case FACE_UP:
                        for (int x = -1; x <= 1; x++) {
                            if (occupation->occupied[(summon->grid_y - 1) *
                                                      grid->width +
                                                      summon->grid_x + x]) {
                                damage->damage[(summon->grid_y - 1) *
                                                grid->width +
                                                summon->grid_x + x] +=
                                                summon->damage;
                                summon->cooldown_timer = 0.f;
                            }
                        }
                        break;
                    case FACE_DOWN:
                        for (int x = -1; x <= 1; x++) {
                            if (occupation->occupied[(summon->grid_y + 1) *
                                                      grid->width +
                                                      summon->grid_x + x]) {
                                damage->damage[(summon->grid_y + 1) *
                                                grid->width +
                                                summon->grid_x + x] +=
                                                summon->damage;
                                summon->cooldown_timer = 0.f;
                            }
                        }
                        break;
                    case FACE_LEFT:
                        for (int y = -1; y <= 1; y++) {
                            if (occupation->occupied[(summon->grid_y + y) *
                                                      grid->width +
                                                      summon->grid_x - 1]) {
                                damage->damage[(summon->grid_y + y) *
                                                grid->width +
                                                summon->grid_x - 1] +=
                                                summon->damage;
                                summon->cooldown_timer = 0.f;
                            }
                        }
                        break;
                    case FACE_RIGHT:
                        for (int y = -1; y <= 1; y++) {
                            if (occupation->occupied[(summon->grid_y + y) *
                                                      grid->width +
                                                      summon->grid_x + 1]) {
                                damage->damage[(summon->grid_y + y) *
                                                grid->width +
                                                summon->grid_x + 1] +=
                                                summon->damage;
                                summon->cooldown_timer = 0.f;
                            }
                        }
                        break;
                    default:
                        break;
                }
                break;
            case WHIRL:
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x != 0 && y != 0) {
                            if (occupation->occupied[(summon->grid_y + y) *
                                                      grid->width +
                                                      summon->grid_x + x]) {
                                damage->damage[(summon->grid_y + y) *
                                                grid->width +
                                                summon->grid_x + x] +=
                                                summon->damage;
                                summon->cooldown_timer = 0.f;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
}
void UpdateDamageGrid(const SummonList* summons, const OccupationGrid* occupation,
                      DamageGrid* damage, Grid* grid,
                      Vector2 map_size, Vector2 origin_offset) {
    for (int j = 0; j < damage->height; j++) {
        for (int i = 0; i < damage->width; i++)
            damage->damage[j * damage->width + i] = 0;
    }
    for (int i = 0; i < summons->last_summon; i++) {
        AttemptCastAbility(&(summons->summons[i]), grid, occupation, damage);
    }
}

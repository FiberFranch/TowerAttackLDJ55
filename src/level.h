#ifndef LEVEL_H_
#define LEVEL_H_

#include <raylib.h>
#include "unit.h"
#include "grid.h"

typedef struct {
    Enemy enemy;
    float time;
} EnemySpawn;

typedef struct {
    EnemySpawn* enemy_spawns;
    int capacity, next_enemy;
} EnemyQueue;

EnemyQueue LoadEnemyQueue(const char* filename);

void DeleteEnemyQueue(EnemyQueue* queue);

Enemy* GetNextEnemy(EnemyQueue* queue, float time);

typedef struct {
    Enemy* enemies;
    int capacity, last_enemy;
} EnemyList;

EnemyList CreateEnemyList(const unsigned int capacity);

void DeleteEnemyList(EnemyList* list);

void AddEnemyToEnemyList(EnemyList* list, Enemy enemy);

void RemoveEnemyFromEnemyList(EnemyList* list, int index);

typedef struct {
    Summon* summons;
    int capacity, last_summon;
} SummonList;

SummonList CreateSummonList(const unsigned int capacity);

void DeleteSummonList(SummonList* list);

void AddSummonToSummonList(SummonList* list, Summon summon);

typedef struct {
    bool* occupied;
    int width, height;
} OccupationGrid;

OccupationGrid CreateOccupationGrid(int width, int height);

void DeleteOccupationGrid(OccupationGrid* grid);

void UpdateOccupationGrid(const EnemyList* enemies,
                          OccupationGrid* occupation, const Grid* grid,
                          Vector2 map_size);

typedef struct {
    int* damage;
    int width, height;
} DamageGrid;

DamageGrid CreateDamageGrid(int width, int height);

void DeleteDamageGrid(DamageGrid* grid);

bool AttemptDealDamage(Summon* summon, const Grid* grid, DamageGrid* damage,
                       const OccupationGrid* occupation, int i, int j);

bool AttemptCastAbility(Summon* summon, const Grid* grid,
                        const OccupationGrid* occupation, DamageGrid* damage);

void UpdateDamageGrid(SummonList* summons, const OccupationGrid* occupation,
                      DamageGrid* damage, const Grid* grid,
                      Vector2 map_size);

typedef struct {
    EnemyQueue spawn_queue;
    Grid grid;
    Summoner summoner;
} Level;

Level LoadLevel(Summoner summoner, const char* grid_file, const char* enemies_file);

void ComputeDirection(int* dir_x, int* dir_y, const Path* path, int index);

int GetNextTile(int tile_x, int tile_y, const Path* path);

void UpdateEnemyPositions(EnemyList* enemies, const Grid* grid,
                          const Path* path, float tile_width,
                          Vector2 map_size);

#endif // LEVEL_H_

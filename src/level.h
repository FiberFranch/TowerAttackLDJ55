#ifndef LEVEL_H_
#define LEVEL_H_

#include <raylib.h>
#include "unit.h"
#include "grid.h"

typedef struct {
    Enemy enemy;
    int time;
} EnemySpawn;

typedef struct {
    EnemySpawn* enemy_spawns;
    int capacity, next_enemy;
} EnemyQueue;

EnemyQueue LoadEnemyQueue(char* filename);

void DeleteEnemyQueue(EnemyQueue* queue);

Enemy* GetNextEnemy(EnemyQueue queue, float time);

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

#endif // LEVEL_H_

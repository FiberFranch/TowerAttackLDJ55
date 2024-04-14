#ifndef LEVEL_H_
#define LEVEL_H_

#include "unit.h"
#include "grid.h"

typedef struct {
    Enemy enemy;
    int time;
} EnemySpawn;

typedef struct {
    EnemySpawn* enemy_spawns;
    int capacity;
    int next_enemy;
} EnemyQueue;

EnemyQueue LoadEnemyQueue(char* filename);

void DeleteEnemyQueue(EnemyQueue* queue);

Enemy* GetNextEnemy(EnemyQueue queue, float time);

typedef struct {
    Enemy* enemies;
    int capacity;
    int last_enemy;
} EnemyList;

EnemyList CreateEnemyList(const unsigned int capacity);

void DeleteEnemyList(EnemyList* list);

void AddEnemyToEnemyList(EnemyList* list, Enemy enemy);

void RemoveEnemyFromEnemyList(EnemyList* list, int index);

typedef struct {
    Summon* summons;
    int size, capacity;
} SummonList;

typedef struct {
    bool* occupied;
    int width, height;
} OccupationGrid;

OccupationGrid CreateOccupationGrid(int width, int height);

void DeleteOccupationGrid(OccupationGrid* grid);

void UpdateOccupationGrid(const EnemyList* enemies,
                          OccupationGrid* occupation);

typedef struct {
    int* damage;
    int width, height;
} DamageGrid;

DamageGrid CreateDamageGrid(int width, int height);

void DeleteDamageGrid(DamageGrid* grid);

void UpdateDamageGrid(const SummonList* summons,
                      const OccupationGrid* occupation,
                      DamageGrid* damage);

typedef struct {
    EnemyQueue spawn_queue;
    Grid grid;
    Summoner summoner;
} Level;

#endif // LEVEL_H_

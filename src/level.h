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
    int next_enemy;
} EnemyList;

EnemyList CreateEnemyList(const unsigned int capacity);

void DeleteEnemyList();

void AddEnemyToEnemyList(EnemyList* list, Enemy enemy);

void RemoveEnemyFromEnemyList(EnemyList* list, int index);

typedef struct {
    EnemyQueue spawn_queue;
    EnemyList current_enemies;
    Grid grid;
    Summoner summoner;
} Level;

#endif // LEVEL_H_

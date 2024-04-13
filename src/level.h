#ifndef LEVEL_H_
#define LEVEL_H_

#include "enemy.h"
#include "grid.h"

typedef struct {
    Enemy enemy;
    int time;
} EnemySpawn;

typedef struct {
    EnemySpawn* enemies;
    int capacity;
    int next_enemy;
} EnemyQueue;

EnemyQueue CreateEnemyQueue();

void DeleteEnemyQueue();

Enemy* GetNextEnemy(EnemyQueue queue, float time);

typedef struct {
} Summoner;

typedef struct {
    Enemy* enemies;
    int capacity;
    int size;
} EnemyList;

EnemyList CreateEnemyList(const unsigned int capacity);

void DeleteEnemyList();

void AddEnemyToEnemyList(EnemyList* list, Enemy enemy);

void DeleteEnemyFromEnemyList(EnemyList* list, int index);

typedef struct {
    EnemyQueue spawn_queue;
    EnemyList current_enemies;
    Grid grid;
    Summoner summoner;
} Level;

#endif // LEVEL_H_

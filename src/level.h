#ifndef LEVEL_H_
#define LEVEL_H_

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

#endif // LEVEL_H_

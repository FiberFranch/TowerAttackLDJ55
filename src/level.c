#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit.h"
#include "level.h"

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
    list.size = 0;
    list.enemies = (Enemy*) calloc(list.capacity, sizeof(Enemy));
}

void DeleteEnemyList(EnemyList* list) {
    Enemy* ptr = list->enemies;
    free(ptr);
}

void AddEnemyToEnemyList(EnemyList* list, Enemy enemy) {
    list.enemies[list.next_enemy] = enemy;
    list.next_enemy++;
}

void RemoveEnemyFromEnemyList(EnemyList* list, int index) {
    for (i = index; i < list.next_enemy - 1; i++) {
        list.enemies[i] = list.enemies[i+1];
    }
    list.next_enemy--;
}

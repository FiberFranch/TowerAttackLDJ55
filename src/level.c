#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemy.h"
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

    EnemyQueue enemies;
    enemies.capacity = capacity;
    enemies.next_enemy = 0;
    enemies.enemies = (EnemySpawn*) calloc(enemies.capacity, sizeof(EnemySpawn));

    char enemy[100];
    int time;
    int i = 0;
    while (fscanf(file, "%s %d", enemy, &time) == 2) {
        enemies.enemies[i].enemy = GetEnemyById(enemy);
        enemies.enemies[i].time = time;
        i++;
    }
    fclose(file);

    return enemies;
}

Enemy* GetNextEnemy(EnemyQueue queue, float time) {
    EnemySpawn* enemy = &queue.enemies[queue.next_enemy];
    if (enemy->time >= time) {
        queue.next_enemy++;
    }
    return &(enemy->enemy);
}

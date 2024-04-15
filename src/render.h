#ifndef RENDER_H_
#define RENDER_H_

#include "level.h"

typedef struct {
    Texture2D* texture;
    Vector3 position;
    float scale;
    Vector3 axis;
    float rotation;
} DrawElement;

int CompareDrawElementDepth(const void* a, const void* b);

typedef struct {
    DrawElement* elements;
    int size, capacity;
} DrawBatch;

DrawBatch CreateDrawBatch(int starting_capacity);

void DestroyDrawBatch(DrawBatch batch);

void AddElementToDrawBatch(DrawBatch* batch, DrawElement element);

void DrawDrawBatch(DrawBatch batch);

void ClearDrawBatch(DrawBatch* batch);

void DrawLevel(Level level);

void DrawEnemy(DrawBatch* batch, const Enemy* enemy, float scale, int number);

void DrawSummon(DrawBatch* batch, const Summon* summon, float scale);


#endif // RENDER_H_

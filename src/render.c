#include "render.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "asset_loader.h"
#include "grid.h"
#include "level.h"
#include "unit.h"

void DrawEnemy(DrawBatch* batch, const Enemy* enemy, float scale, int number) {
    float displacement = 0.03f * (sin(5.0f * GetTime()) + 1.0f);
    float rotation = 2.0f * sin(5.0f*GetTime() + 5.0f * number);
    DrawElement element;
    element.texture = enemy->sprite;
    element.position = (Vector3){enemy->position.x, displacement, enemy->position.y};
    element.axis = (Vector3){0.0f, 0.0f, 1.0f};
    element.rotation = rotation;
    element.scale = 1.0f / scale;
    AddElementToDrawBatch(batch, element);
}

void DrawSummon(DrawBatch* batch, const Summon* summon, float scale) {
    float displacement = 0.03f * (sin(5.0f * GetTime()) + 1.0f);
    DrawElement element;
    element.texture = summon->sprite;
    element.position = (Vector3){summon->position.x, displacement, summon->position.y};
    element.axis = (Vector3){0.0f, 0.0f, 1.0f};
    element.rotation = 0.0f;
    element.scale = 1.0f / scale;
    AddElementToDrawBatch(batch, element);
}

int CompareDrawElementDepth(const void* a, const void* b) {
    const DrawElement* A = (DrawElement*) a;
    const DrawElement* B = (DrawElement*) b;

    if (A->position.z < B->position.z) return -1;
    if (A->position.z > B->position.z) return 1;
    else return 0;
}

void ClearDrawBatch(DrawBatch* batch) {
    batch->size = 0;
}

DrawBatch CreateDrawBatch(int starting_capacity) {
    DrawBatch batch;
    batch.size = 0;
    batch.elements = calloc(starting_capacity, sizeof(DrawElement));
    batch.capacity = starting_capacity;
    return batch;
}

void DestroyDrawBatch(DrawBatch batch) { free(batch.elements); }

void AddElementToDrawBatch(DrawBatch* batch, DrawElement element) {
    if (batch->size >= batch->capacity) {
        batch->capacity *= 2;
        batch->elements = realloc(batch->elements, batch->capacity * sizeof(DrawElement));
    }

    batch->elements[batch->size] = element;
    batch->size++;
}

void DrawDrawBatch(DrawBatch batch) {
    qsort(batch.elements, batch.size, sizeof(DrawElement), CompareDrawElementDepth);
    Model model = *GetModelById(MODEL_ID_rectangle);
    for (int i = 0; i < batch.size; i++) {
        DrawElement element = batch.elements[i];
        printf("x = %f, y = %f\n", element.position.x, element.position.z);
        model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = *element.texture;
        DrawModelEx(model, element.position,
                    element.axis, element.rotation,
                    (Vector3){element.scale, element.scale, element.scale},
                    WHITE);
    }
}

void AddElementToDrawBatch(DrawBatch* batch, DrawElement element);

Camera CreateCamera() {
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 5.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    return camera;
};

Model CreateHeightMapFromGrid(const Grid* grid, float dimension) {
    const unsigned int ImageWidth = 360;
    const unsigned int ImageHeight = 360;
    const float MaxHeight = 1.0f;
    const float HeightOndulations = 0.00f * MaxHeight;
    Image heightmapImage;

    heightmapImage.mipmaps = 1;
    heightmapImage.width = ImageWidth;
    heightmapImage.height = ImageHeight;
    heightmapImage.format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE;
    heightmapImage.data = calloc(ImageHeight * ImageWidth, sizeof(char));

    Image* pathImage = GetSpriteById(SPRITE_ID_path);
    Image* defaultImage = GetSpriteById(SPRITE_ID_default);
    Color* pathColors = LoadImageColors(*pathImage);
    Color* defaultColors = LoadImageColors(*defaultImage);
    Image mapDiffuseImage = {0};
    mapDiffuseImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    mapDiffuseImage.mipmaps = 1;
    mapDiffuseImage.width = grid->width * defaultImage->width;
    mapDiffuseImage.height = grid->height * defaultImage->height;
    mapDiffuseImage.data = calloc(mapDiffuseImage.width*mapDiffuseImage.height, 4*sizeof(char));
    Image mapTilesImage = {0};
    mapTilesImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    mapTilesImage.mipmaps = 1;
    mapTilesImage.width = grid->width * defaultImage->width;
    mapTilesImage.height = grid->height * defaultImage->height;
    mapTilesImage.data = calloc(mapDiffuseImage.width*mapDiffuseImage.height, 4*sizeof(char));
    // Construct the diffuse image from the tiles
    for (unsigned int i = 0; i < grid->width; i++) {
        for (unsigned int j = 0; j < grid->height; j++) {
            Color* colors;
            const GridTile* tile = GetTileFromGrid(grid, i, j);
            if (tile->type == PATH_TILE ||
                tile->type == START_TILE ||
                tile->type == SUMMONER_TILE ||
                tile->type == END_TILE) {
                colors = pathColors;
            }
            else {
                colors = defaultColors;
            }
            // Assign the colors to the region
            for (unsigned int x = 0; x < defaultImage->width; x++) {
                for (unsigned int y = 0; y < defaultImage->height; y++) {
                    const unsigned int index =(x + defaultImage->width*i) + mapDiffuseImage.width * (y + defaultImage->height*j);
                    /* printf("index %i / %i\n", index, mapDiffuseImage.width * mapDiffuseImage.height); */
                    ((Color*)mapDiffuseImage.data)[index] = colors[x + defaultImage->width * y];
                    unsigned int gridIndex =  (unsigned int)(i + grid->width * j);
                    *(unsigned int*)(&((Color*)mapTilesImage.data)[index]) = gridIndex; // Set grid index
                }
            }
        }
    }

    for (unsigned int i = 0; i < ImageWidth; i++) {
        for (unsigned int j = 0; j < ImageHeight; j++) {
            // From image coords to grid coords
            const unsigned int grid_x = (unsigned int) (((float) i / (float) ImageWidth) * (float)grid->width);
            const unsigned int grid_y = (unsigned int) (((float) j / (float) ImageHeight) * (float)grid->height);

            // Compute the height
            float height = MaxHeight;
            const GridTile* tile0 = GetTileFromGrid(grid, grid_x, grid_y);
            if (tile0->type == PATH_TILE ||
                tile0->type == START_TILE ||
                tile0->type == END_TILE) {
                height = 0.0f;
            }
            if (tile0->type == SUMMONER_TILE) {
                height = 2*MaxHeight;
            }

            ((char*)heightmapImage.data)[i + ImageWidth * j] = (char) height;
        }
    }

    Mesh heightmap_mesh = GenMeshHeightmap(heightmapImage, (Vector3){dimension, 10.0, dimension});
    Model heightmap_model = LoadModelFromMesh(heightmap_mesh);
    heightmap_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTextureFromImage(mapDiffuseImage);
    heightmap_model.materials[0].maps[MATERIAL_MAP_NORMAL].texture = LoadTextureFromImage(mapTilesImage);
    heightmap_model.materials[0].shader = *GetShaderById(SHADER_ID_map);

    UnloadImageColors(defaultColors);
    UnloadImageColors(pathColors);
    UnloadImage(mapDiffuseImage);
    UnloadImage(mapTilesImage);
    UnloadImage(heightmapImage);
    return heightmap_model;
}

typedef struct {
    int* data;
    unsigned int width, height;
} GridLookup;

void UnloadGridLookup(GridLookup lookup) {
    free(lookup.data);
}

GridLookup LoadGridLookup(Camera camera, Model levelHeightMap, Vector3 position) {
    // Render the indices
    RenderTexture2D FBO = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    levelHeightMap.materials[0].shader = *GetShaderById(SHADER_ID_lookup);
    BeginTextureMode(FBO);
    ClearBackground(WHITE);
    BeginMode3D(camera);
    DrawModel(levelHeightMap, position, 1.0, WHITE);
    EndMode3D();
    EndTextureMode();

    Image renderedImage = LoadImageFromTexture(FBO.texture);
    /* ExportImage(renderedImage, "result.png"); */
    Color* colors = LoadImageColors(renderedImage);

    GridLookup lookup = {0};
    lookup.width = FBO.texture.width;
    lookup.height = FBO.texture.height;
    lookup.data = calloc(lookup.width * lookup.height, sizeof(int));
    for (unsigned int i = 0; i < lookup.width; i++) {
        for (unsigned int j = 0; j < lookup.height; j++) {
            const int index = i + lookup.width * j;
            const int index_flipped = i + lookup.width * (lookup.height - j - 1);
            Color color = colors[index_flipped];
            color.a = 0;
            unsigned int tile_index = *(unsigned int*)(&color);
            lookup.data[index] = (int) tile_index;
        }
    }

    levelHeightMap.materials[0].shader = *GetShaderById(SHADER_ID_map);
    UnloadImage(renderedImage);
    UnloadImageColors(colors);
    UnloadRenderTexture(FBO);

    return lookup;
}

static int lastScreenWidth, lastScreenHeight;
void UpdateGridLookupIfResolutionChanges(GridLookup *lookup, Camera camera, Model levelHeightMap, Vector3 position) {
    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();
    if (currentHeight != lastScreenHeight || currentWidth != lastScreenWidth) {
        printf("lastWidth = %i, currentWidth = %i \n", lastScreenHeight, currentWidth);
        lastScreenHeight = currentHeight;
        lastScreenWidth = currentWidth;
        UnloadGridLookup(*lookup);
        *lookup = LoadGridLookup(camera, levelHeightMap, position);
    }
}

int GetGridIndexFromScreen(GridLookup lookup) {
    Vector2 pos = GetMousePosition();
    int index = ((int)pos.x) + lookup.width * ((int)pos.y);
    /* printf("index = %i\n", lookup.data[index]); */
    return lookup.data[index];
}

void DrawLevel(Level level) {
    Camera camera = CreateCamera();

    const float map_size = 5.0f;
    const Vector3 offset = (Vector3){-0.5f *map_size, 0.0, -0.5f *map_size};
    Grid grid = level.grid;
    const float scalex = ((float)grid.width) / map_size;

    EnemyQueue queue = level.spawn_queue;
    EnemyList enemy_list = CreateEnemyList(queue.capacity);
    SummonList summon_list = CreateSummonList(5);
    AddSummonToSummonList(&summon_list, CreateSummonEvaristo());
    AddSummonToSummonList(&summon_list, CreateSummonEvaristo());
    AddSummonToSummonList(&summon_list, CreateSummonEvaristo());
    int selected_summon_id = 0;
    Summon selected_summon_unit;
    SummonOrientation selected_summon_orientation = FACE_DOWN;

    SummonList summoned_units = CreateSummonList(grid.width * grid.height);

    Path path = CreatePathFromGrid(&grid);
    PathSampler sampler = CreatePathSampler(&grid, path, (Vector2){map_size, map_size});
    Vector2 summonerPos = GetTileTypeWorldPosition(&grid, (Vector2){map_size, map_size}, SUMMONER_TILE);
    Vector2 startingPos = GetTileTypeWorldPosition(&grid, (Vector2){map_size, map_size}, START_TILE);
    EnemyQueueSetStartingPosition(&queue, startingPos);
    Model heightmap_model = CreateHeightMapFromGrid(&grid, map_size);

    int SelectedTileLoc = GetShaderLocation(*GetShaderById(SHADER_ID_map), "selectedTile");
    int IsPlacableLoc = GetShaderLocation(*GetShaderById(SHADER_ID_map), "isPlacable");
    int selectedTile = 1000000;
    int isPlacable = 0;
    GridLookup lookup = LoadGridLookup(camera, heightmap_model, offset);

    DrawBatch drawBatch = CreateDrawBatch(1);

    float time = 0.0f;
    while (!WindowShouldClose())
    {
        time += 1.0f / 60.0f;
        if (enemy_list.last_enemy > 0) {
            UpdateEnemyPositions(&enemy_list, &grid, sampler, (Vector2){map_size, map_size});
        }

        //printf("time = %f\n", time);
        Enemy* enemy = GetNextEnemy(&queue, time);
        if (enemy) {
            AddEnemyToEnemyList(&enemy_list, *enemy);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            selectedTile = GetGridIndexFromScreen(lookup);
            if (selectedTile < grid.width * grid.height) {
                if (grid.grid[selectedTile].type == DEFAULT_TILE
                    && !grid.grid[selectedTile].occupied) {
                    selected_summon_unit = summon_list.summons[selected_summon_id];
                    selected_summon_unit.grid_x = grid.grid[selectedTile].grid_x;
                    selected_summon_unit.grid_y = grid.grid[selectedTile].grid_y;
                    AddSummonToSummonList(&summoned_units, selected_summon_unit);
                    grid.grid[selectedTile].occupied = true;
                }
            }
        }

        if (IsKeyPressed(KEY_E)) {
            selected_summon_id++;
            if (selected_summon_id >= summon_list.last_summon)
                selected_summon_id = 0;
        }
        
        if (IsKeyPressed(KEY_Q)) {
            selected_summon_id--;
            if (selected_summon_id < 0)
                selected_summon_id = summon_list.last_summon - 1;
        }

        UpdateGridLookupIfResolutionChanges(&lookup, camera, heightmap_model, offset);
        selectedTile = GetGridIndexFromScreen(lookup);
        if (selectedTile < grid.width * grid.height) {
            if (grid.grid[selectedTile].type == DEFAULT_TILE
                && !grid.grid[selectedTile].occupied)
                isPlacable = 1;
            else isPlacable = 0;
        }
        SetShaderValue(*GetShaderById(SHADER_ID_map), SelectedTileLoc, &selectedTile, SHADER_UNIFORM_INT);
        SetShaderValue(*GetShaderById(SHADER_ID_map), IsPlacableLoc, &isPlacable, SHADER_UNIFORM_INT);

        BeginDrawing();
        ClearBackground(DARKGRAY);
        /* UpdateCamera(&camera, CAMERA_FREE); */
        BeginMode3D(camera);
        DrawModel(heightmap_model, offset, 1.0, WHITE);
        DrawSummoner(scalex, summonerPos);
        if (selectedTile < grid.width * grid.height) {
            if (grid.grid[selectedTile].type == DEFAULT_TILE
                && !grid.grid[selectedTile].occupied)
                DrawSummoner(scalex, GetWorldPositionFromGrid(&grid, (Vector2){scalex, scalex}, grid.grid[selectedTile].grid_x, grid.grid[selectedTile].grid_y));
        }

        for (int i = 0; i < enemy_list.last_enemy; i++ ) {
            Enemy* enemy = &enemy_list.enemies[i];
            DrawEnemy(&drawBatch, enemy, 0.5f * scalex, i);
        }

        for (int i = 0; i < summoned_units.last_summon; i++ ) {
            Summon* summon = &summoned_units.summons[i];
            DrawSummon(&drawBatch, summon, 0.5f * scalex);
        }

        DrawDrawBatch(drawBatch);
        EndMode3D();

        DrawFPS(50,50);
        EndDrawing();
        ClearDrawBatch(&drawBatch);
    }

    DestroyDrawBatch(drawBatch);
    DestroyPathSampler(sampler);
    DeleteEnemyList(&enemy_list);
    DeleteEnemyQueue(&queue);
    UnloadGridLookup(lookup);
    UnloadModel(heightmap_model);
}

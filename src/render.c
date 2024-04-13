#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "asset_loader.h"
#include "grid.h"

// typedef struct LevelState LevelState;
// typedef struct Level Level;

// void DrawLevel(const Level* level, const LevelState* state) {

Camera CreateCamera() {
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 6.0f }; // Camera position
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
    Image mapDiffuseImage;
    mapDiffuseImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    mapDiffuseImage.mipmaps = 1;
    mapDiffuseImage.width = grid->width * defaultImage->width;
    mapDiffuseImage.height = grid->height * defaultImage->height;
    mapDiffuseImage.data = calloc(mapDiffuseImage.width*mapDiffuseImage.height, 4*sizeof(char));

    // Construct the diffuse image from the tiles
    for (unsigned int i = 0; i < grid->width; i++) {
        for (unsigned int j = 0; j < grid->height; j++) {
            Color* colors;
            const GridTile* tile = GetTileFromGrid(grid, i, j);
            if (tile->type == PATH_TILE) {
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
            float height = 0.0f;
            const GridTile* tile0 = GetTileFromGrid(grid, grid_x, grid_y);
            if (tile0->type != PATH_TILE) {
                height = MaxHeight;
            }

            ((char*)heightmapImage.data)[i + ImageWidth * j] = (char) height;
        }
    }

    Mesh heightmap_mesh = GenMeshHeightmap(heightmapImage, (Vector3){dimension, dimension, dimension});
    Model heightmap_model = LoadModelFromMesh(heightmap_mesh);
    heightmap_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTextureFromImage(mapDiffuseImage);
    heightmap_model.materials[0].shader = *GetShaderById(SHADER_ID_lighting);

    free(heightmapImage.data);
    return heightmap_model;
}

void DrawLevel() {
    Camera camera = CreateCamera();

    const float map_size = 5.0f;
    const Vector3 offset = (Vector3){-0.5f *map_size, 0.0, -0.5f *map_size};
    Grid grid = LoadGrid("assets/map_test.png");
    Model heightmap_model = CreateHeightMapFromGrid(&grid, map_size);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        /* UpdateCamera(&camera, CAMERA_FREE); */

        BeginMode3D(camera);
        DrawModel(heightmap_model, offset, 1.0, WHITE);
        EndMode3D();

        EndDrawing();
    }

    UnloadModel(heightmap_model);
}

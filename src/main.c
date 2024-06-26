#include <raylib.h>

#include "asset_loader.h"
#include "render.h"

void InitializeGame() {
    const int initialScreenWidth = 1920;
    const int initialScreenHeight = 1080; // 16:9
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(initialScreenWidth, initialScreenHeight, "Test");
    /* SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED); */
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();

    LoadAllAssets();

    SetTargetFPS(60);
}

void DeinitializeGame() {
    UnloadAllAssets();

    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
}

int main(void)
{
    InitializeGame();

    Summoner summoner;
    Level level = LoadLevel(summoner, "assets/map_test.png", "assets/test_queue.txt");
    DrawLevel(level);

    DeinitializeGame();

    return 0;
};

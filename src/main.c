#include <raylib.h>

#include "asset_loader.h"
#include "render.h"

void InitializeGame() {
    const int initialScreenWidth = 800;
    const int initialScreenHeight = 450; // 16:9
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(initialScreenWidth, initialScreenHeight, "Test");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
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

    DrawLevel();

    DeinitializeGame();

    return 0;
};

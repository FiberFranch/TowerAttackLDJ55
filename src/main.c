#include "raylib.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int initialScreenWidth = 800;
    const int initialScreenHeight = 450; // 16:9
    InitWindow(initialScreenWidth, initialScreenHeight, "Test");
    SetWindowState(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
    InitAudioDevice();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
};

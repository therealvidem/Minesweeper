#include <raylib.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand(time(NULL));

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Minesweeper");

    Image titleIcon = LoadImage("assets/icon.dds");
    SetWindowIcon(titleIcon);

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(RAYWHITE);

        

        EndDrawing();

    }

    UnloadImage(titleIcon);

    CloseWindow();

    return 0;
}
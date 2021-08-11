#include <raylib.h>
#include <minesweeper.h>
#include "graphics/textures.h"
#include "graphics/board_graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_TILE_SET_SIZE 256
#define BOARD_TILE_SIZE 16

int main(void)
{
    srand(time(NULL));

    const unsigned screenWidth = 600;
    const unsigned screenHeight = 600;
    const unsigned boardWidth = 9;
    const unsigned boardHeight = 9;
    const unsigned amountMines = 10;

    InitWindow(screenWidth, screenHeight, "Minesweeper");

    Image titleIcon = LoadImage("assets/icon.dds");
    SetWindowIcon(titleIcon);

    Textures textures = {
        .boardTilset = LoadTexture("assets/tileset.png"),
        .boardTileSize = { .x = BOARD_TILE_SIZE, .y = BOARD_TILE_SIZE },
    };
    BoardTile tile = 0;
    for (int y = 0; y < BOARD_TILE_SET_SIZE / 4; y += BOARD_TILE_SIZE)
    {
        for (int x = 0; x < BOARD_TILE_SET_SIZE / 4; x += BOARD_TILE_SIZE)
        {
            textures.boardTileRecs[tile].x = x;
            textures.boardTileRecs[tile].y = y;
            textures.boardTileRecs[tile].width = BOARD_TILE_SIZE;
            textures.boardTileRecs[tile].height = BOARD_TILE_SIZE;
            tile++;
        }
    }

    MinesweeperGame *game = (MinesweeperGame *)malloc(sizeof(MinesweeperGame));
    InitGame(game, boardWidth, boardHeight);
    StartGame(
        game,
        GetRandomValue,
        (size_t)amountMines,
        (Point){ .x = boardWidth/2, .y = boardHeight/2 }
    );

    Vector2 boardScale = { .x = 4.0f, .y = 4.0f };
    Vector2 boardDrawSize = GetBoardDrawSize(&(game->mines), &textures, boardScale);
    Vector2 boardPos = {
        .x = screenWidth/2.f - boardDrawSize.x/2.f,
        .y = screenHeight/2.f - boardDrawSize.y/2.f,
    };

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawBoard(
            &(game->mines),
            &textures,
            BT_MINE,
            BT_OPENED,
            boardPos,
            boardScale
        );

        DrawText(
            TextFormat("(%d, %d)", GetMouseX(), GetMouseY()),
            10,
            10,
            10,
            BLACK
        );

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadImage(titleIcon);
    UnloadTexture(textures.boardTilset);
    FreeGame(game);

    CloseWindow();

    return 0;
}
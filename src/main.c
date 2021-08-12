#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

#include <minesweeper.h>
#include "graphics/textures.h"
#include "graphics/board_graphics.h"
#include "input/board_input.h"
#include "game_struct.h"

#define BOARD_TILE_SET_SIZE 256
#define BOARD_TILE_SIZE 16

int main(void)
{
    srand(time(NULL));

#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif

    const unsigned screenWidth = 720;
    const unsigned screenHeight = 720;
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
    BoardTile currentTile = 0;
    for (float y = 0.f; y < (float)BOARD_TILE_SET_SIZE / 4.f; y += (float)BOARD_TILE_SIZE)
    {
        for (float x = 0.f; x < (float)BOARD_TILE_SET_SIZE / 4.f; x += (float)BOARD_TILE_SIZE)
        {
            textures.boardTileRecs[currentTile].x = x;
            textures.boardTileRecs[currentTile].y = y;
            textures.boardTileRecs[currentTile].width = BOARD_TILE_SIZE;
            textures.boardTileRecs[currentTile].height = BOARD_TILE_SIZE;
            currentTile++;
        }
    }

    BoardTile numbersTiles[NUM_NUMBERS + 1];
    numbersTiles[0] = BT_OPENED;
    for (int i = 0; i < 8; i++)
    {
        numbersTiles[i + 1] = BT_1 + i;
    }

    BoardTile flagsTiles[NUM_FLAGS + 1] = {
        BT_NOTHING,
        BT_FLAG,
        BT_QUESTION,
    };

    const Vector2 boardScale = { .x = 5.f, .y = 5.f };
    const Vector2 boardDrawSize = GetBoardDrawSize(boardWidth, boardHeight, &textures, boardScale);
    const Vector2 boardOffset = {
        .x = screenWidth/2.f - boardDrawSize.x/2.f,
        .y = screenHeight/2.f - boardDrawSize.y/2.f,
    };
    
    GameStruct gameStruct = (GameStruct){
        .game = (MinesweeperGame *)malloc(sizeof(MinesweeperGame)),
        .textures = &textures,
        .amountMines = amountMines,
        .boardScale = boardScale,
        .boardDrawSize = boardDrawSize,
        .boardOffset = boardOffset,
        .lastOpenedPoint = (Point){ 0, 0 },
    };

    InitGame(gameStruct.game, boardWidth, boardHeight);

    SetTargetFPS(60);

    float wonTextHueValue = 0;
    float wonTextPosX = (float)(-MeasureText("You Won!", 32));

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        HandleBoardInput(&gameStruct);

        if (gameStruct.gameState == GS_WON)
        {
            wonTextHueValue = wonTextHueValue + 250.f * GetFrameTime();
            if (wonTextHueValue > 360.f)
            {
                wonTextHueValue = 0.f;
            }
            wonTextPosX = wonTextPosX + 200.f * GetFrameTime();
            if (wonTextPosX > (float)(screenWidth + MeasureText("You Won!", 32)))
            {
                wonTextPosX = (float)(-MeasureText("You Won!", 32));
            }
        }

        if (HasWonGame(gameStruct.game) && gameStruct.gameState != GS_WON)
        {
            gameStruct.gameState = GS_WON;
            FillBoard(&(gameStruct.game->opened), (ARRAY_T)true);
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        switch (gameStruct.gameState)
        {
        case GS_ALIVE:
        case GS_INITIAL:
            {
                DrawBoard(
                    &(gameStruct.game->numbers),
                    &textures,
                    numbersTiles,
                    NUM_NUMBERS + 1,
                    boardOffset,
                    boardScale
                );

                DrawMarkedBoard(
                    &(gameStruct.game->opened),
                    &textures,
                    BT_CLOSED,
                    BT_NOTHING,
                    boardOffset,
                    boardScale
                );

                DrawBoard(
                    &(gameStruct.game->flags),
                    &textures,
                    flagsTiles,
                    NUM_FLAGS + 1,
                    boardOffset,
                    boardScale
                );
            } break;
        case GS_DEAD:
            {
                DrawBoard(
                    &(gameStruct.game->numbers),
                    &textures,
                    numbersTiles,
                    NUM_NUMBERS + 1,
                    boardOffset,
                    boardScale
                );

                // DrawBoard(
                //     &(gameStruct.game->flags),
                //     &textures,
                //     flagsTiles,
                //     NUM_FLAGS + 1,
                //     boardOffset,
                //     boardScale
                // );

                DrawMarkedBoard(
                    &(gameStruct.game->mines),
                    &textures,
                    BT_NOTHING,
                    BT_MINE,
                    boardOffset,
                    boardScale
                );

                DrawCell(
                    &textures,
                    gameStruct.lastOpenedPoint,
                    BT_RED_MINE,
                    boardOffset,
                    boardScale
                );

                DrawText(
                    "Game Over!",
                    screenWidth/2 - MeasureText("Game Over!", 32)/2,
                    screenHeight/2 - 32,
                    32,
                    BLACK
                );
            } break;
        case GS_WON:
            {
               DrawBoard(
                    &(gameStruct.game->numbers),
                    &textures,
                    numbersTiles,
                    NUM_NUMBERS + 1,
                    boardOffset,
                    boardScale
                );

                DrawMarkedBoard(
                    &(gameStruct.game->opened),
                    &textures,
                    BT_CLOSED,
                    BT_NOTHING,
                    boardOffset,
                    boardScale
                );

                // DrawBoard(
                //     &(gameStruct.game->flags),
                //     &textures,
                //     flagsTiles,
                //     NUM_FLAGS + 1,
                //     boardOffset,
                //     boardScale
                // );

                DrawMarkedBoard(
                    &(gameStruct.game->mines),
                    &textures,
                    BT_NOTHING,
                    BT_MINE,
                    boardOffset,
                    boardScale
                );

                DrawText(
                    "You Won!",
                    wonTextPosX,
                    screenHeight/2 - 32,
                    32,
                    ColorFromHSV(wonTextHueValue, 1.f, 1.f)
                );
            } break;
        }

#ifndef NDEBUG
        DrawText(
            TextFormat("(%d, %d)", GetMouseX(), GetMouseY()),
            20,
            20,
            16,
            BLACK
        );
#endif

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadImage(titleIcon);
    UnloadTexture(textures.boardTilset);
    FreeGame(gameStruct.game);

    CloseWindow();

    return 0;
}
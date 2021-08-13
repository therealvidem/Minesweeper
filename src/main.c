#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <raylib.h>

#include <minesweeper.h>
#include "graphics/textures.h"
#include "graphics/board_graphics.h"
#include "input/board_input.h"
#include "game_struct.h"
#include "state_handler.h"

#define BOARD_TILE_SET_SIZE 256
#define BOARD_TILE_SIZE 16

const unsigned screenWidth = 720;
const unsigned screenHeight = 720;
const unsigned boardWidth = 9;
const unsigned boardHeight = 9;
const unsigned amountMines = 10;

void DrawNumbers(GameStruct *gameStruct, BoardTile numbersTiles[NUM_NUMBERS + 1], Vector2 boardOffset, Vector2 boardScale)
{
    DrawBoard(
        gameStruct->game->numbers,
        gameStruct->textures,
        numbersTiles,
        NUM_NUMBERS + 1,
        boardOffset,
        boardScale
    );
}

void DrawOpened(GameStruct *gameStruct, Vector2 boardOffset, Vector2 boardScale)
{
    DrawMarkedBoard(
        gameStruct->game->opened,
        gameStruct->textures,
        BT_CLOSED,
        BT_NOTHING,
        boardOffset,
        boardScale
    );
}

void DrawFlags(GameStruct *gameStruct, BoardTile flagsTiles[NUM_FLAGS + 1], Vector2 boardOffset, Vector2 boardScale)
{
    DrawBoard(
        gameStruct->game->flags,
        gameStruct->textures,
        flagsTiles,
        NUM_FLAGS + 1,
        boardOffset,
        boardScale
    );
}

void DrawMines(GameStruct *gameStruct, Vector2 boardOffset, Vector2 boardScale)
{
    DrawMarkedBoard(
        gameStruct->game->mines,
        gameStruct->textures,
        BT_NOTHING,
        BT_MINE,
        boardOffset,
        boardScale
    );
}

void DrawTime(GameStruct *gameStruct)
{
    double finalTime = ((double)gameStruct->endTime.tv_sec + (double)gameStruct->endTime.tv_usec*1e-6) - ((double)gameStruct->startTime.tv_sec + (double)gameStruct->startTime.tv_usec*1e-6);
    DrawText(
        TextFormat("Time: %.4lfs", finalTime),
        screenWidth/2 - MeasureText(TextFormat("Time: %.4lfs", finalTime), 32)/2,
        screenHeight/2 + 16,
        32,
        BLACK
    );
}

int main(void)
{
    srand(time(NULL));

#ifndef NDEBUG
    SetTraceLogLevel(LOG_DEBUG);
#endif

    InitWindow(screenWidth, screenHeight, "Minesweeper");

    Image titleIcon = LoadImage("assets/icon.dds");
    SetWindowIcon(titleIcon);
    UnloadImage(titleIcon);

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
        .gameState = GS_INITIAL,
        .textures = &textures,
        .amountMines = amountMines,
        .boardScale = boardScale,
        .boardDrawSize = boardDrawSize,
        .boardOffset = boardOffset,
        .lastOpenedPoint = (Point){ 0, 0 },
        .mineHitPoint = (Point){ 0, 0 },
        .startTime = (struct timeval){0},
        .endTime = (struct timeval){0},
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
            ChangeGameState(&gameStruct, GS_WON);
            FillBoard(gameStruct.game->opened, (ARRAY_T)true);
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
                DrawNumbers(&gameStruct, numbersTiles, boardOffset, boardScale);
                DrawOpened(&gameStruct, boardOffset, boardScale);
                DrawFlags(&gameStruct, flagsTiles, boardOffset, boardScale);
            } break;
        case GS_DEAD:
            {
                DrawNumbers(&gameStruct, numbersTiles, boardOffset, boardScale);
                DrawOpened(&gameStruct, boardOffset, boardScale);
                DrawMines(&gameStruct, boardOffset, boardScale);

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

                DrawTime(&gameStruct);
            } break;
        case GS_WON:
            {
                DrawNumbers(&gameStruct, numbersTiles, boardOffset, boardScale);
                DrawOpened(&gameStruct, boardOffset, boardScale);
                DrawFlags(&gameStruct, flagsTiles, boardOffset, boardScale);

                DrawText(
                    "You Won!",
                    wonTextPosX,
                    screenHeight/2 - 32,
                    32,
                    ColorFromHSV(wonTextHueValue, 1.f, 1.f)
                );

                DrawTime(&gameStruct);
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
    
    FreeGame(gameStruct.game);

    // Ironically, this results in a segmentation fault.
    // UnloadImage(titleIcon);
    
    UnloadTexture(textures.boardTilset);

    CloseWindow();

    return 0;
}

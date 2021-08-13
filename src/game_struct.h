#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include <raylib.h>
#include <sys/time.h>
#include <minesweeper.h>
#include "graphics/textures.h"

typedef enum
{
    GS_INITIAL,
    GS_ALIVE,
    GS_DEAD,
    GS_WON,
} GameState;

// The GameStruct holds all the necessary components of the game, such as
// the texture as well as the MinesweeperGame struct itself.
typedef struct
{
    MinesweeperGame *game;
    Textures *textures;

    unsigned amountMines;
    Vector2 boardScale;
    Vector2 boardDrawSize;
    Vector2 boardOffset;

    GameState gameState;
    Point lastOpenedPoint;
    Point mineHitPoint;
    struct timeval startTime;
    struct timeval endTime;
} GameStruct;

#endif

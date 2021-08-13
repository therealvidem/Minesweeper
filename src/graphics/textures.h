#ifndef TEXTURES_H
#define TEXTURES_H

#include <raylib.h>

typedef enum
{
    BT_CLOSED,
    BT_OPENED,
    BT_FLAG,
    BT_QUESTION,
    BT_MINE,
    BT_RED_MINE,
    BT_1,
    BT_2,
    BT_3,
    BT_4,
    BT_5,
    BT_6,
    BT_7,
    BT_8,
    BT_OPENED_QUESTION,
    BT_NOTHING,
} BoardTile;
#define NUM_BOARD_TILES ((BT_NOTHING - BT_CLOSED) + 1)

typedef struct
{
    Texture2D boardTilset;
    Vector2 boardTileSize;
    Rectangle boardTileRecs[NUM_BOARD_TILES];
} Textures;

#endif

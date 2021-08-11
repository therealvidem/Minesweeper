#ifndef BOARD_GRAPHICS_H
#define BOARD_GRAPHICS_H

#include <raylib.h>
#include <minesweeper.h>
#include "textures.h"

void DrawBoard(const Board *board, const Textures *textures, BoardTile markedTile, BoardTile unmarkedTile, Vector2 position, Vector2 scale);
Vector2 GetBoardDrawSize(const Board *board, const Textures *textures, Vector2 scale);

#endif

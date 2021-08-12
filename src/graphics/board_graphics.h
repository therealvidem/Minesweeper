#ifndef BOARD_GRAPHICS_H
#define BOARD_GRAPHICS_H

#include <raylib.h>
#include <minesweeper.h>
#include "../game_struct.h"
#include "textures.h"

// Draw `board` using `textures` and `tiles`.
// `tiles` should be an array with `numTiles` amount of BoardTiles.
// The drawn board's top-left position on the screen will be set to `offset`
// and the board will be scaled (with the origin being 0,0 relative to the board)
// according to `scale`.
// Note: If a cell's value goes beyond the bounds of `tiles`, the default
// tile to be drawn will be the first tile in `tiles` (i.e., `tiles[0]`).
void DrawBoard(const Board *board, const Textures *textures, const BoardTile *tiles, size_t numTiles, Vector2 offset, Vector2 scale);

// Similarly to DrawBoard(), draws a board with 0 and 1 marks. A value of 0 (unmarked) in a
// cell will draw `unmarkedTile`, while a value of 1 (marked) will draw `markedTile`.
void DrawMarkedBoard(const Board *board, const Textures *textures, BoardTile unmarkedTile, BoardTile markedTile, Vector2 offset, Vector2 scale);

// void DrawNumbersBoard(const Board *board, const Textures *textures, BoardTile numbersTiles[NUM_NUMBERS], BoardTile noneTile, Vector2 offset, Vector2 scale);

// Draws a single cell at `cellPoint` using `textures` and `cellTile`.
// `offset` and `scale` will be used to offset and scale the drawn cell.
void DrawCell(const Textures *textures, Point cellPoint, BoardTile cellTile, Vector2 offset, Vector2 scale);

// Given a board's `boardWidth` and `boardHeight`, this calculates the
// bounds of the board as drawn.
Vector2 GetBoardDrawSize(INDEX_T boardWidth, INDEX_T boardHeight, const Textures *textures, Vector2 scale);

#endif

#ifndef BOARD_INPUT_H
#define BOARD_INPUT_H

#include <raylib.h>
#include <minesweeper.h>
#include "../game_struct.h"

// Gets the nearest point to the given `position` and sets it to `outPoint`.
// Returns true if a point was found, otherwise false.
Point GetNearestPoint(GameStruct *gameStruct, Vector2 position, Point *outPoint);

// Handles the left-clicking portion of `HandleBoardInput` for various
// actions, such as opening a cell.
// Note: If the mouse clicked on a valid point, then this sets
// `gameStruct->lastClickedPoint` to the clicked point.
// Returns true if: 1) a cell was found at the mouse, and 2) the cell was not flagged.
// Returns false otherwise.
bool HandleLeftClickCell(GameStruct *gameStruct);

// Handles the left-clicking portion of `HandleBoardInput` for various
// actions, primarily the flagging of cells.
void HandleRightClickCell(GameStruct *gameStruct);

// Handles input relating to the board, primarily the clicking of cells.
void HandleBoardInput(GameStruct *gameStruct);

#endif

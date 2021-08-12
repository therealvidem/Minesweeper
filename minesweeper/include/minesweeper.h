#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <time.h>
#include "board.h"

typedef struct
{
    Board mines;
    Board flags;
    Board numbers;
    Board opened;
    time_t startTime;

    INDEX_T width;
    INDEX_T height;
    INDEX_T amountCells;
} MinesweeperGame;

// Generates a random point within the bounds of the game space.
Point GetRandomPoint(MinesweeperGame *game, int (*rng)(int, int));

// Returns true `point` is at a mine, false otherwise.
bool IsPointMine(MinesweeperGame *game, Point point);

// Returns true `point` is at a flag (or question), false otherwise.
bool IsPointFlag(MinesweeperGame *game, Point point);

// Returns true `point` is open, false otherwise.
bool IsPointOpen(MinesweeperGame *game, Point point);

// Initializes `game` to default values and clears all boards.
// Note this does not initialize startTime, which StartGame() does.
void InitGame(MinesweeperGame *game, INDEX_T width, INDEX_T height);

// Randomly generates a set amount of mines.
void GenerateMines(MinesweeperGame *game, int (*rng)(int, int), INDEX_T amount);

// Starts `game` by starting the timer and revealing the cells at `startPoint`.
// Returns true if the initial `startPoint` is within the board, false otherwise.
bool StartGame(MinesweeperGame *game, int (*rng)(int, int), INDEX_T amountMines, Point startPoint);

// Opens a single cell without recursively opening empty cells around.
// Returns the CT_NONE if the cell is flagged or was already opened, otherwise
// returns the CellType that was opened.
CellType OpenSingleCell(MinesweeperGame *game, Point point);

// Flags a (closed) cell. This goes through a rotation between 3 states:
//     normal closed cell -> flagged closed cell -> questioned closed cell -> normal closed cell
// If the cell is found to be not closed (i.e., marked inside `game->opened`), then does not do anything.
// Returns the new CellType of the cell (CT_CLOSED, CT_FLAG, or CT_QUESTION) IF the cell is overall closed.
// Otherwise, return CT_NONE.
CellType FlagCell(MinesweeperGame *game, Point point);

// Returns true if the current board is a winning board, e.g., all non-mines have
// been opened, false otherwise.
bool HasWonGame(const MinesweeperGame *game);

// Resets `game` to its initial state.
// Note: This does not call StartGame(). It merely resets the
// fields of `game` so that StartGame() may safely be called after.
void ResetGame(MinesweeperGame *game);

void FreeGame(MinesweeperGame *game);

#endif

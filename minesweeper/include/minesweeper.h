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
    Board revealed;
    bool alive;
    time_t startTime;

    INDEX_T width;
    INDEX_T height;
    INDEX_T amountCells;
} MinesweeperGame;

// Initializes `game` to default values and clears all boards.
// Note this does not initialize startTime, which StartGame() does.
void InitGame(MinesweeperGame *game, INDEX_T width, INDEX_T height);

// Randomly generates a set amount of mines.
void GenerateMines(MinesweeperGame *game, int (*rngGen)(int, int), INDEX_T amount);

// Starts `game` by starting the timer and revealing the cells at `startPoint`.
// Returns true if the initial `startPoint` is within the board, false otherwise.
bool StartGame(MinesweeperGame *game, int (*rngGen)(int, int), INDEX_T amountMines, Point startPoint);

// Returns true if the current board is a winning board, e.g., all non-mines have
// been revealed, false otherwise.
bool HasWonGame(const MinesweeperGame *game);

void FreeGame(MinesweeperGame *game);

#endif

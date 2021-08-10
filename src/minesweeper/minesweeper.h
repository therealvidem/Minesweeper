#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "board.h"
#include <stdlib.h>
#include <time.h>

typedef struct minesweeperGame
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
void InitGame(MinesweeperGame *game);

// Randomly generates a set amount of mines.
void GenerateMines(MinesweeperGame *game, INDEX_T amount);

// Starts `game` by starting the timer and revealing the cells at `startPoint`.
// Returns true 
bool StartGame(MinesweeperGame *game, INDEX_T amountMines, Point startPoint);

// Returns true if the current board is a winning board, e.g., all non-mines have
// been revealed, false otherwise.
bool HasWonGame(const MinesweeperGame *game);

#endif

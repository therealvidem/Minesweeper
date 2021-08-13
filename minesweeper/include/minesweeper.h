#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include "board.h"
#include "../point_queue.h"

typedef struct
{
    Board *mines;
    Board *flags;
    Board *numbers;
    Board *opened;

    INDEX_T width;
    INDEX_T height;
    INDEX_T amountCells;
} MinesweeperGame;

typedef struct
{
    MinesweeperGame *game;
    Point startPoint;
    PointQueue *queue;
    unsigned currentIteration;
} CellOpeningQueue;

// Generates a random point within the bounds of the game space.
Point GetRandomPoint(MinesweeperGame *game, int (*rng)(int, int));

// Returns true if `point` is at a mine, false otherwise.
bool IsPointMine(MinesweeperGame *game, Point point);

// Returns true if `point` is at a flag (or question), false otherwise.
bool IsPointFlag(MinesweeperGame *game, Point point);

// Note: This does NOT check whether `point` is in the board.
// IsPointInBoard() must be checked prior to calling this function.
// Returns true if `point` has a number that is not 0, false otherwise.
bool IsPointNumbered(MinesweeperGame *game, Point point);

// Returns true if `point` has a number of 0, i.e., it is empty and has no mines around it.
bool IsPointEmpty(MinesweeperGame *game, Point point);

// Returns true if `point` is open, false otherwise.
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
// Returns CRS_FAILED if the cell is flagged or was already opened, otherwise
// returns the CellReturnStatus that was opened.
CellReturnStatus OpenSingleCell(MinesweeperGame *game, Point point);

// Allocates and initializes a CellOpeningQueue.
// Note: This means it must eventually be freed using FreeCellOpeningQueue().
CellOpeningQueue *CreateCellOpeningQueue(MinesweeperGame *game, Point startPoint);

// Makes `ff` perform the next iteration of the flood fill algorithm.
// Returns CRS_OPEN_QUEUE_STOPPED if the flood filling has stopped, 
// CRS_FAILED if the opened cell was either: flagged, mine, or already opened, otherwise
// returns the CellReturnStatus that was opened.
CellReturnStatus IterateFloodFiller(CellOpeningQueue *ff);

// Attempts to initiate the chording of a cell. This will return
// a CellOpeningQueue with all neighbors queued if the cell at `startPoint` is
// a valid cell from which to chord. Otherwise, it will return NULL. 
// Note: If a CellOpeningQueue is returned, it must eventually be freed using FreeCellOpeningQueue().
// Returns a pointer to a CellOpeningQueue with all neighbors queued, otherwise NULL.
CellOpeningQueue *ChordCell(MinesweeperGame *game, Point startPoint);

// Makes `chordQueue` perform the next iteration of chording.
// Returns CRS_OPEN_QUEUE_STOPPED if the chording has stopped,
// CRS_FAILED if the opened cell was flagged or already opened, otherwise
// returns the CellReturnStatus that was opened.
CellReturnStatus IterateChord(CellOpeningQueue *chordQueue);

// Flags a (closed) cell. This goes through a rotation between 3 states:
//     normal closed cell -> flagged closed cell -> questioned closed cell -> normal closed cell
// If the cell is found to be not closed (i.e., marked inside `game->opened`), then does not do anything.
// Returns the new CellReturnStatus of the cell (CRS_CLOSED, CRS_FLAG, or CRS_QUESTION) IF the cell is overall closed.
// Otherwise, return CRS_FAILED.
CellReturnStatus FlagCell(MinesweeperGame *game, Point point);

// Returns true if the current board is a winning board, e.g., all non-mines have
// been opened, false otherwise.
bool HasWonGame(const MinesweeperGame *game);

// Resets `game` to its initial state.
// Note: This does not call StartGame(). It merely resets the
// fields of `game` so that StartGame() may safely be called after.
void ResetGame(MinesweeperGame *game);

void FreeGame(MinesweeperGame *game);

void FreeCellOpeningQueue(CellOpeningQueue *openQueue);

#endif

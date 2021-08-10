#ifndef BOARD_H
#define BOARD_H

#include <raylib.h>
#include "types.h"
#include "point.h"

const int neighborCellsX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int neighborCellsY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int numNeighbors = 8;
// Gets the coordinates of the ith neighbor of `point` (from 0 to 7).
// This is a macro defined as a comma-separated pair of values: x, y of the neighbor cell.
// To use this, do:
//   ```
//   for (int i = 0; i < numNeighbors; i++)
//   {
//       INDEX_T neighborX, neighborY = GET_NEIGHBOR_CELL_INDEX(point, i);
//       // can now do stuff like IsBoardMarkedAtPoint(board, Point{neighborX, neighborY})
//   }
//   ```
#define GET_NEIGHBOR_CELL_INDEX(point, i) point.x + neighborCellsX[i], point.y + neighborCellsY[i]

#define IS_POINT_IN_BOARD(board, point) InBounds(point, board->width, board->height)

typedef struct board
{
    ARRAY_T *_arr;

    INDEX_T width;
    INDEX_T height;
} Board;

// Checks if the index within the bounds of the board array.
bool IsIndexInBoard(const Board *board, INDEX_T index);

// Creates a board and also dynamically allocates the board array.
// This means the board should be disposed of (using `FreeBoard(board)`).
Board CreateBoard(INDEX_T width, INDEX_T height);

// Convert `point` from a 2D index to a 1D index for accessing the array.
INDEX_T GetIndexFromPoint(const Board *board, Point point);

// Also checks that the point is within bounds of the board array.
// Returns true if successfully set, false otherwise.
ARRAY_T GetValueAtPoint(const Board *board, Point point);

// Does *not* check that the index is within bounds of the board array.
void SetValueAtIndex(Board *board, INDEX_T index, ARRAY_T newValue);

// Also checks that the index is within bounds of the board array.
// Returns true if successfully set, false otherwise.
bool SetValueAtPoint(Board *board, Point point, ARRAY_T newValue);

// Returns true if the cell at `index` exists and is marked 
// (i.e., 1 inside the array), false otherwise.
bool IsBoardMarkedAtIndex(const Board *board, INDEX_T index);

// Returns true if the cell at `point` exists and is marked
// (i.e., 1 inside the array), false otherwise.
bool IsBoardMarkedAtPoint(const Board *board, Point point);

// Returns true if the cell was (successfully) changed, false otherwise.
bool MarkBoardAtIndex(Board *board, INDEX_T index);

// Returns true if the cell was (successfully) changed, false otherwise.
bool MarkBoardAtPoint(Board *board, Point point);

#endif

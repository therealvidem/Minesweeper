#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "point.h"

extern const int neighborCellsX[];
extern const int neighborCellsY[];
extern const int numNeighbors;
// Gets the coordinates of the ith neighbor of `point` (from 0 to 7).
// The order of the neighbors start at the top-left (when viewing top-left corner as x = 0, y = 0), then
// goes clockwise. So, the 0th neighbor of (4, 5) is (3, 4), the 1st neighbor is (3, 5), the
// 2nd neighbor is (3, 6), the 3rd neighbor is (4, 6), and so on and so forth.
// NOTE: This does NOT check whether the point is out of bounds of a board. This
// can be checked with IsPointInBoard().
// This is a macro defined as a comma-separated pair of values: x, y of the neighbor cell.
// To use this, do:
//   ```
//   for (int i = 0; i < numNeighbors; i++)
//   {
//       Point neighborPoint = GET_NEIGHBOR_POINT(point, i);
//       // can now do stuff like IsBoardMarkedAtPoint(board, neighborPoint)
//   }
//   ```
#define GET_NEIGHBOR_POINT(point, i) { .x = point.x + neighborCellsX[i], .y = point.y + neighborCellsY[i] }

typedef struct board
{
    ARRAY_T *_arr;

    INDEX_T width;
    INDEX_T height;
    INDEX_T amountMarked;
} Board;

// Checks if the `index` is within the bounds of the board array.
bool IsIndexInBoard(const Board *board, INDEX_T index);

// Checks if the `point` is within the bounds of the board array.
bool IsPointInBoard(const Board *board, Point point);

// Creates a board and also dynamically allocates the board array.
// This means the board should be disposed of (using `FreeBoard(board)`).
Board CreateBoard(INDEX_T width, INDEX_T height);

// Convert `point` from a 2D index to a 1D index for accessing the array.
INDEX_T GetIndexFromPoint(const Board *board, Point point);

// Convert `index` from a 1D index to a 2D point.
Point GetPointFromIndex(const Board *board, INDEX_T index);

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

// Returns true if the cell was (successfully) changed, false otherwise.
bool UnmarkBoardAtIndex(Board *board, INDEX_T index);

// Returns true if the cell was (successfully) changed, false otherwise.
bool UnmarkBoardAtPoint(Board *board, Point point);

// Frees the `board` that was dynamically allocated.
void FreeBoard(Board *board);

#endif

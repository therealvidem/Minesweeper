#ifndef BOARD_H
#define BOARD_H

#include <raylib.h>
#include "types.h"
#include "point.h"

const int NEIGHBOR_CELLS_X[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int NEIGHBOR_CELLS_Y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
// Gets the coordinates of the ith neighbor of `point` (from 0 to 7)
#define GET_NEIGHBOR_CELL(point, i) point.x + NEIGHBOR_CELLS_X[i], point.y + NEIGHBOR_CELLS_Y[i]

typedef struct board
{
    // A bit array stored inside a single long long (int) value.
    BITARRAY_T _value;

    POINT_T width;
    POINT_T height;
} Board;

Board CreateBoard(POINT_T width, POINT_T height);

// The bit mask has a single activated bit at `point` inside the `bitArray`.
BITARRAY_T GetBitMaskAtPoint(const Board *board, Point point);

// The bit mask has a single activated bit at `index` inside the `bitArray`.
BITARRAY_T GetBitMaskAtIndex(const Board *board, BITARRAY_T index);

// Returns true if the cell at `point` exists and is marked 
// (or 1 in terms of a bit), false otherwise.
bool IsBoardMarkedAtPoint(const Board *board, Point point);

// Returns true if the cell at `index` exists and is marked 
// (or 1 in terms of a bit), false otherwise.
bool IsBoardMarkedAtIndex(const Board *board, BITARRAY_T index);

// Returns true if the cell at `point` exists and is marked 
// (or 1 in terms of a bit), false otherwise.
bool IsBoardMarkedAtPoint(const Board *board, Point point);

// Returns true if the cell at `index` exists and is marked 
// (or 1 in terms of a bit), false otherwise.
bool IsBoardMarkedAtIndex(const Board *board, BITARRAY_T index);

// Returns true if the cell was (successfully) changed, false otherwise.
bool MarkBoardAtPoint(Board *board, Point point);

// Returns true if the cell was (successfully) changed, false otherwise.
bool MarkBoardAtIndex(Board *board, BITARRAY_T index);

#endif

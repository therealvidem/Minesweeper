#ifndef POINT_H
#define POINT_H

#include "types.h"

#define InBoard(board, point) InBounds(point, board->width, board->height)

// A simple point in a board with an POINT_T int x and POINT_T int y.
// Index starts at 0.
typedef struct point
{
    POINT_T x;
    POINT_T y;
} Point;

int InBounds(Point point, POINT_T width, POINT_T height);

#endif

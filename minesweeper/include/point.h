#ifndef POINT_H
#define POINT_H

#include "types.h"

// A simple point in a board with an INDEX_T int x and INDEX_T int y.
// Index starts at 0.
typedef struct
{
    INDEX_T x;
    INDEX_T y;
} Point;

bool InBounds(Point point, INDEX_T width, INDEX_T height);

// Determines if `p1` and `p2` are one step from each other, counting
// diagonals as one step.
// i.e., determines if
//   X X X
//   X 1 X
//   X X X
// `p2` is any one of the X's surrounding 1 (p1), and vice versa.
bool ArePointNeighbors(Point p1, Point p2);

#endif

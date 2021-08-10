#ifndef POINT_H
#define POINT_H

#include "types.h"

// A simple point in a board with an INDEX_T int x and INDEX_T int y.
// Index starts at 0.
typedef struct point
{
    INDEX_T x;
    INDEX_T y;
} Point;

bool InBounds(Point point, INDEX_T width, INDEX_T height);

#endif

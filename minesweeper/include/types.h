#ifndef MINESWEEPER_TYPES_H
#define MINESWEEPER_TYPES_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#define ARRAY_T int
#define INDEX_T size_t
#define NUM_NUMBERS 8
#define NUM_FLAGS 2

// CellReturnStatus is a general enum used to indicate either the status of the
// function, or the cell value of the action. For instance, OpenSingleCell()
// has a chance of failing, in which case it will return CRS_FAILED, otherwise
// it will just return the correspoding cell type that was successfully opened.
typedef enum
{
    CRS_OPEN_QUEUE_STOPPED = -2,
    CRS_FAILED = -1,
    CRS_0 = 0,
    CRS_1 = 1,
    CRS_2 = 2,
    CRS_3 = 3,
    CRS_4 = 4,
    CRS_5 = 5,
    CRS_6 = 6,
    CRS_7 = 7,
    CRS_8 = 8,
    CRS_MINE,
    CRS_CLOSED,
    CRS_FLAG,
    CRS_QUESTION,
} CellReturnStatus;

#endif

#ifndef MINESWEEPER_TYPES_H
#define MINESWEEPER_TYPES_H

#include <math.h>
#include <stdbool.h>

#define ARRAY_T int
#define INDEX_T size_t
#define NUM_NUMBERS 8
#define NUM_FLAGS 2

typedef enum
{
    CT_NONE,
    CT_1,
    CT_2,
    CT_3,
    CT_4,
    CT_5,
    CT_6,
    CT_7,
    CT_8,
    CT_EMPTY,
    CT_MINE,
    CT_CLOSED,
    CT_FLAG,
    CT_QUESTION,
} CellType;

#endif

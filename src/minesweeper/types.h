#ifndef MINESWEEPER_TYPES_H
#define MINESWEEPER_TYPES_H

#include <math.h>
#include <stdbool.h>

#define BITARRAY_T unsigned long long
#define POINT_T unsigned

#define MAX_BITARRAY_T_SIZE 1 << (8 * sizeof(BITARRAY_T))
#define MAX_BITARRAY_T_WIDTH_HEIGHT (BITARRAY_T)sqrt(MAX_BIT_ARRAY_T_SIZE)

#endif

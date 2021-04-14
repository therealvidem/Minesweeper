#include "board.h"

Board CreateBoard(POINT_T width, POINT_T height)
{
    return (Board){(BITARRAY_T)0, width, height};
}

BITARRAY_T GetMaskAtPoint(const Board *board, Point point)
{
    return ((BITARRAY_T)1 << ((point.y + 1) * board->width)) << (point.x + 1);
}

BITARRAY_T GetMaskAtIndex(const Board *board, BITARRAY_T index)
{
    return (BITARRAY_T)1 << index;
}

bool IsBoardMarkedAtPoint(const Board *board, Point point)
{
    if (InBoard(board, point))
        return GetMaskAtPoint(board, point) & board->_value;
    return 0;
}

bool IsBoardMarkedAtIndex(const Board *board, BITARRAY_T index)
{
    if (index < board->width * board->height)
        return GetMaskAtIndex(board, index) & board->_value;
    return 0;
}

bool MarkBoardAtPoint(Board *board, Point point)
{
    if (!IsBoardMarkedAtPoint(board, point))
        return board->_value |= GetMaskAtPoint(board, point);
    return 0;
}

bool MarkBoardAtIndex(Board *board, BITARRAY_T index)
{
    if (!IsBoardMarkedAtIndex(board, index))
        return board->_value |= GetMaskAtIndex(board, index);
    return 0;
}

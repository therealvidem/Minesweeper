#include "board.h"

bool IsIndexInBoard(const Board *board, ARRAY_T index)
{
    return index < board->width * board->height;
}

Board CreateBoard(INDEX_T width, INDEX_T height)
{
    ARRAY_T *_arr = MemAlloc(sizeof(ARRAY_T) * width * height);
    return (Board){_arr, width, height};
}

INDEX_T GetIndexFromPoint(const Board *board, Point point)
{
    return (point.y * board->width) + point.x;
}

ARRAY_T GetValueAtPoint(const Board *board, Point point)
{
    INDEX_T index = GetIndexFromPoint(board, point);
    return board->_arr[index];
}

void SetValueAtIndex(Board *board, INDEX_T index, ARRAY_T newValue)
{
    board->_arr[index] = newValue;
}

bool SetValueAtPoint(Board *board, Point point, ARRAY_T newValue)
{
    if (IS_POINT_IN_BOARD(board, point))
    {
        SetValueAtIndex(board, GetIndexFromPoint(board, point), newValue);
        return true;
    }
    return false;
}

bool IsBoardMarkedAtIndex(const Board *board, INDEX_T index)
{
    if (IsIndexInBoard(board, index))
        return board->_arr[index] == (ARRAY_T)true;
    return false;
}

bool IsBoardMarkedAtPoint(const Board *board, Point point)
{
    if (IS_POINT_IN_BOARD(board, point))
        return board->_arr == (ARRAY_T)true;
    return false;
}

bool MarkBoardAtIndex(Board *board, INDEX_T index)
{
    if (!IsBoardMarkedAtIndex(board, index))
        board->_arr[index] = (ARRAY_T)true;
        return true;
    return false;
}

bool MarkBoardAtPoint(Board *board, Point point)
{
    if (!IsBoardMarkedAtPoint(board, point))
        SetValueAtPoint(board, point, (ARRAY_T)true);
        return true;
    return false;
}

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

void SetValueAtIndex(Board *board, INDEX_T index, ARRAY_T new_value)
{
    board->_arr[index] = new_value;
}

bool SetValueAtPoint(Board *board, Point point, ARRAY_T new_value)
{
    if (IsPointInBoard(board, point))
    {
        SetValueAtIndex(board, GetIndexFromPoint(board, point), new_value);
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
    if (IsPointInBoard(board, point))
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

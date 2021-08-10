#include "board.h"

bool IsIndexInBoard(const Board *board, ARRAY_T index)
{
    return index < board->width * board->height;
}

bool IsPointInBoard(const Board *board, Point point)
{
    return InBounds(point, board->width, board->height);
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

Point GetPointFromIndex(const Board *board, INDEX_T index)
{
    INDEX_T y = index / board->width;
    INDEX_T x = y - board->width;
    Point point = {
        .x = x,
        .y = y,
    };
    return point;
}

ARRAY_T GetValueAtPoint(const Board *board, Point point)
{
    INDEX_T index = GetIndexFromPoint(board, point);
    return board->_arr[index];
}

void SetValueAtIndex(Board *board, INDEX_T index, ARRAY_T newValue)
{
    ARRAY_T lastValue = board->_arr[index];
    board->_arr[index] = newValue;
    if (newValue != (ARRAY_T)false && lastValue == (ARRAY_T)false)
    {
        board->amountMarked++;
    }
    else if (newValue == (ARRAY_T)false && lastValue != (ARRAY_T)false)
    {
        board->amountMarked--;
    }
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
        return board->_arr[index] != (ARRAY_T)false;
    return false;
}

bool IsBoardMarkedAtPoint(const Board *board, Point point)
{
    if (IS_POINT_IN_BOARD(board, point))
        return board->_arr != (ARRAY_T)false;
    return false;
}

bool MarkBoardAtIndex(Board *board, INDEX_T index)
{
    if (!IsBoardMarkedAtIndex(board, index))
        SetValueAtIndex(board, index, (ARRAY_T)true);
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

bool UnmarkBoardAtIndex(Board *board, INDEX_T index)
{
    if (IsBoardMarkedAtIndex(board, index))
        SetValueAtIndex(board, index, (ARRAY_T)false);
        return true;
    return false;
}

bool UnmarkBoardAtPoint(Board *board, Point point)
{
    if (IsBoardMarkedAtPoint(board, point))
        SetValueAtPoint(board, point, (ARRAY_T)false);
        return true;
    return false;
}

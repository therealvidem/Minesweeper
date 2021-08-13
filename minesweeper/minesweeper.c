#include "include/minesweeper.h"

void InitGame(MinesweeperGame *game, INDEX_T width, INDEX_T height)
{
    game->width = width;
    game->height = height;
    game->amountCells = width * height;
    game->mines = CreateBoard(width, height);
    game->flags = CreateBoard(width, height);
    game->numbers = CreateBoard(width, height);
    game->opened = CreateBoard(width, height);
    game->startTime = (time_t)0;
}

Point GetRandomPoint(MinesweeperGame *game, int (*rng)(int, int))
{
    return (Point){
        .x = rng(0, game->width - 1),
        .y = rng(0, game->height - 1),
    };
}

bool IsPointMine(MinesweeperGame *game, Point point)
{
    return IsBoardMarkedAtPoint(game->mines, point);
}

bool IsPointFlag(MinesweeperGame *game, Point point)
{
    return IsBoardMarkedAtPoint(game->flags, point);
}

bool IsPointNumbered(MinesweeperGame *game, Point point)
{
    return GetValueAtPoint(game->numbers, point) != 0;
}

bool IsPointEmpty(MinesweeperGame *game, Point point)
{
    return !IsBoardMarkedAtPoint(game->numbers, point);
}

bool IsPointOpen(MinesweeperGame *game, Point point)
{
    return IsBoardMarkedAtPoint(game->opened, point);
}

void GenerateMines(MinesweeperGame *game, int (*rng)(int, int), INDEX_T amount)
{
    if (amount >= game->amountCells)
        amount = game->amountCells;
    
    // TODO: Maybe a smarter mine generation algorithm here?
    size_t currentAmountMines = 0;
    while (currentAmountMines < amount)
    {
        Point minePoint = GetRandomPoint(game, rng);
        if (MarkBoardAtPoint(game->mines, minePoint))
        {
            currentAmountMines++;
        }
    }
    // for (INDEX_T i = 0; i < amount; i++)
    // {
    //     bool validPoint = false;
    //     Point minePoint;
    //     while (!validPoint)
    //     {
    //         minePoint.x = rng(0, game->width);
    //         minePoint.y = rng(0, game->height);
    //         validPoint = !IsPointFlag(game, minePoint);
    //     }
    //     MarkBoardAtPoint(game->mines, minePoint);
    // }
}

// Count the number of mines around each cell in `game->numbers`, then 
// set that cell's value to that amount.
void UpdateNumbers(MinesweeperGame *game)
{
    for (INDEX_T i = 0; i < game->amountCells; i++)
    {
        Point point = GetPointFromIndex(game->numbers, i);
        INDEX_T numMines = 0;
        for (INDEX_T neighborIndex = 0; neighborIndex < numNeighbors; neighborIndex++)
        {
            Point neighborPoint = GET_NEIGHBOR_POINT(point, neighborIndex);
            if (IsBoardMarkedAtPoint(game->mines, neighborPoint))
            {
                numMines++;
            }
        }
        SetValueAtPoint(game->numbers, point, numMines);
    }
}

void ReplaceMine(MinesweeperGame *game, int (*rng)(int, int), Point originalPoint, Point startPoint)
{
    UnmarkBoardAtPoint(game->mines, originalPoint);
                    
    // Places the mine at another point, ensuring that the new
    // point is not a neighbor of `startPoint` again.
    // This ensures that the number of mines stays consistent.
    Point newPoint;
    bool validNewPoint = false;
    while (!validNewPoint)
    {
        newPoint = GetRandomPoint(game, rng);
        validNewPoint = !ArePointNeighbors(newPoint, startPoint) && !IsPointMine(game, newPoint);
    }
    MarkBoardAtPoint(game->mines, newPoint);
}

bool StartGame(MinesweeperGame *game, int (*rng)(int, int), INDEX_T amountMines, Point startPoint)
{
    if (IsPointInBoard(game->opened, startPoint))
    {
        GenerateMines(game, rng, amountMines);
        
        // Ensures no neighbors of `startPoint` are mines.
        // This is to allow for easier openings.
        // TODO: Make this a configurable option.
        for (INDEX_T neighborIndex = 0; neighborIndex < numNeighbors; neighborIndex++)
        {
            Point neighborPoint = GET_NEIGHBOR_POINT(startPoint, neighborIndex);
            if (IsPointInBoard(game->mines, neighborPoint))
            {
                if (IsPointMine(game, neighborPoint))
                {
                    ReplaceMine(game, rng, neighborPoint, startPoint);
                }

                // if (!IsPointFlag(game, neighborPoint))
                // {
                //     MarkBoardAtPoint(game->opened, neighborPoint);
                // }
            }
        }

        if (IsPointMine(game, startPoint))
        {
            ReplaceMine(game, rng, startPoint, startPoint);
        }
        // MarkBoardAtPoint(game->opened, startPoint);

        UpdateNumbers(game);

        // FloodFiller *ff = CreateFloodFiller(game, startPoint);

        // bool opening = true;
        // while (opening)
        // {
        //     if (IterateFloodFiller(ff) == CRS_FLOODFILL_STOPPED)
        //     {
        //         opening = false;
        //     }
        // }

        // FreeFloodFiller(ff);

        game->startTime = clock();
        return true;
    }
    return false;
}

CellReturnStatus OpenSingleCell(MinesweeperGame *game, Point point)
{
    if (IsPointOpen(game, point) || IsPointFlag(game, point))
    {
        return CRS_FAILED;
    }

    CellReturnStatus cellTypeOpened = CRS_FAILED;
    if (IsPointMine(game, point))
    {
        cellTypeOpened = CRS_MINE;
    }
    else
    {
        cellTypeOpened = GetValueAtPoint(game->numbers, point);
    }

    MarkBoardAtPoint(game->opened, point);
    return cellTypeOpened;
}

FloodFiller *CreateFloodFiller(MinesweeperGame *game, Point startPoint)
{
    FloodFiller *ff = (FloodFiller *)malloc(sizeof(FloodFiller));
    PointQueue *queue = CreatePointQueue();
    ff->game = game;
    ff->startPoint = startPoint;
    ff->queue = queue;
    ff->currentIteration = 0;

    EnqueuePointQueue(queue, startPoint);
    return ff;
}

CellReturnStatus IterateFloodFiller(FloodFiller *ff)
{
    if (!IsPointQueueEmpty(ff->queue))
    {
        // TODO: FIX FLOOD FILLER
        Point pointToOpen = DequeuePointQueue(ff->queue);
        bool isInBoard = IsPointInBoard(ff->game->opened, pointToOpen);
        bool isOpen = IsPointOpen(ff->game, pointToOpen);
        bool isFlag = IsPointFlag(ff->game, pointToOpen);
        bool isMine = IsPointMine(ff->game, pointToOpen);

        if (isInBoard && !isOpen && !isFlag && !isMine)
        {
            CellReturnStatus openedCellType = OpenSingleCell(ff->game, pointToOpen);

            if (IsPointEmpty(ff->game, pointToOpen))
            {
                for (INDEX_T neighborIndex = 0; neighborIndex < numNeighbors; neighborIndex++)
                {
                    Point neighborPoint = GET_NEIGHBOR_POINT(pointToOpen, neighborIndex);
                    EnqueuePointQueue(ff->queue, neighborPoint);
                }
            }

            ff->currentIteration++;

            return openedCellType;
        }
        
        return CRS_FAILED;
    }
    return CRS_FLOODFILL_STOPPED;
}

CellReturnStatus FlagCell(MinesweeperGame *game, Point point)
{
    if (!IsPointOpen(game, point))
    {
        switch (GetValueAtPoint(game->flags, point))
        {
        // Closed -> Flagged
        case 0:
            {
                SetValueAtPoint(game->flags, point, 1);
                return CRS_FLAG;
            }
        // Flagged -> Questioned
        case 1:
            {
                SetValueAtPoint(game->flags, point, 2);
                return CRS_QUESTION;
            }
        // Questioned -> Closed
        case 2:
            {
                SetValueAtPoint(game->flags, point, 0);
                return CRS_CLOSED;
            }
        default:
            break;
        }
    }
    return CRS_FAILED;
}

bool HasWonGame(const MinesweeperGame *game)
{
    return (game->amountCells - game->mines->amountMarked) == game->opened->amountMarked;
}

void ResetGame(MinesweeperGame *game)
{
    ClearBoard(game->mines);
    ClearBoard(game->flags);
    ClearBoard(game->numbers);
    ClearBoard(game->opened);
    game->startTime = (time_t)0;
}

void FreeGame(MinesweeperGame *game)
{
    if (game != NULL)
    {
        FreeBoard(game->mines);
        FreeBoard(game->flags);
        FreeBoard(game->numbers);
        FreeBoard(game->opened);
        free(game);
    }
}

void FreeFloodFiller(FloodFiller *ff)
{
    if (ff != NULL)
    {
        FreePointQueue(ff->queue);
        free(ff);
    }
}

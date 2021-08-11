#include "include/minesweeper.h"

void InitGame(MinesweeperGame *game, INDEX_T width, INDEX_T height)
{
    game->width = width;
    game->height = height;
    game->amountCells = width * height;
    game->mines = CreateBoard(width, height);
    game->flags = CreateBoard(width, height);
    game->numbers = CreateBoard(width, height);
    game->revealed = CreateBoard(width, height);
    game->alive = false;
    game->startTime = (time_t)0;
}

void GenerateMines(MinesweeperGame *game, int (*rngGen)(int, int), INDEX_T amount)
{
    if (amount >= game->amountCells)
        amount = game->amountCells;
    
    // TODO: Maybe a smarter mine generation algorithm here?
    size_t currentAmountMines = 0;
    while (currentAmountMines < amount)
    {
        Point minePoint = {
            .x = rngGen(0, game->width - 1),
            .y = rngGen(0, game->height - 1),
        };
        if (MarkBoardAtPoint(&(game->mines), minePoint))
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
    //         minePoint.x = rngGen(0, game->width);
    //         minePoint.y = rngGen(0, game->height);
    //         validPoint = !IsBoardMarkedAtPoint(&(game->mines), minePoint);
    //     }
    //     MarkBoardAtPoint(&(game->mines), minePoint);
    // }
}

// Count the number of mines around each cell in `game->numbers`, then 
// set that cell's value to that amount.
void UpdateNumbers(MinesweeperGame *game)
{
    for (INDEX_T i = 0; i < game->amountCells; i++)
    {
        Point point = GetPointFromIndex(&(game->numbers), i);
        INDEX_T numMines = 0;
        for (INDEX_T neighborIndex = 0; neighborIndex < numNeighbors; neighborIndex++)
        {
            Point neighborPoint = GET_NEIGHBOR_POINT(point, neighborIndex);
            if (IsBoardMarkedAtPoint(&(game->mines), neighborPoint))
            {
                numMines++;
            }
        }
        SetValueAtPoint(&(game->numbers), point, numMines);
    }
}

bool StartGame(MinesweeperGame *game, int (*rngGen)(int, int), INDEX_T amountMines, Point startPoint)
{
    if (IsPointInBoard(&(game->revealed), startPoint))
    {
        GenerateMines(game, rngGen, amountMines);
        
        // Ensures no neighbors of `startPoint` are mines.
        // This is to allow for easier openings.
        // TODO: Make this a configurable option.
        for (INDEX_T neighborIndex = 0; neighborIndex < numNeighbors; neighborIndex++)
        {
            Point neighborPoint = GET_NEIGHBOR_POINT(startPoint, neighborIndex);
            if (IsPointInBoard(&(game->mines), neighborPoint))
            {
                if (IsBoardMarkedAtPoint(&(game->mines), neighborPoint))
                {
                    UnmarkBoardAtPoint(&(game->mines), neighborPoint);
                }
                MarkBoardAtPoint(&(game->revealed), neighborPoint);
            }
        }
        MarkBoardAtPoint(&(game->revealed), startPoint);

        UpdateNumbers(game);

        game->startTime = clock();
        return true;
    }
    return false;
}

bool HasWonGame(const MinesweeperGame *game)
{
    return (game->amountCells - game->mines.amountMarked) == game->revealed.amountMarked;
}

void FreeGame(MinesweeperGame *game)
{
    if (game != NULL)
    {
        FreeBoard(&(game->mines));
        FreeBoard(&(game->flags));
        FreeBoard(&(game->numbers));
        FreeBoard(&(game->revealed));
        free(game);
    }
}

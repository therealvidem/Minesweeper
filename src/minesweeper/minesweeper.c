#include "minesweeper.h"

void InitGame(MinesweeperGame *game)
{
    game->mines = CreateBoard(game->width, game->height);
    game->flags = CreateBoard(game->width, game->height);
    game->numbers = CreateBoard(game->width, game->height);
    game->revealed = CreateBoard(game->width, game->height);
    game->amountCells = game->width * game->height;
    game->alive = false;
    game->startTime = (time_t)0;
}

void GenerateMines(MinesweeperGame *game, INDEX_T amount)
{
    if (amount >= game->amountCells)
        amount = game->amountCells;
    
    // TODO: Maybe a smarter mine generation algorithm here?
    size_t currentAmountMines = 0;
    while (currentAmountMines < amount)
    {
        Point minePoint = {
            .x = GetRandomValue(0, game->width),
            .y = GetRandomValue(0, game->height),
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
    //         minePoint.x = GetRandomValue(0, game->width);
    //         minePoint.y = GetRandomValue(0, game->height);
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

bool StartGame(MinesweeperGame *game, INDEX_T amountMines, Point startPoint)
{
    if (IS_POINT_IN_BOARD(game, startPoint))
    {
        GenerateMines(game, amountMines);
        
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
    }
    return false;
}

bool HasWonGame(const MinesweeperGame *game)
{
    return (game->amountCells - game->mines.amountMarked) == game->revealed.amountMarked;
}

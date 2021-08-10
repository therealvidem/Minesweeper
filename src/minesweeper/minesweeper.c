#include "minesweeper.h"

void InitGame(MinesweeperGame *game, unsigned amountMines)
{
    game->mines = CreateBoard(game->width, game->height);
    game->flags = CreateBoard(game->width, game->height);
    game->numbers = CreateBoard(game->width, game->height);
    game->alive = false;
    game->startTime = (time_t)0;

    GenerateMines(game, amountMines);
}

void GenerateMines(MinesweeperGame *game, unsigned amount)
{
    unsigned amountCells = game->width * game->height;
    if (amount >= amountCells)
        amount = amountCells;
    
    for (int i = 0; i < amountCells; i++)
    {
        // TODO: Implement generating mines
    }
}

bool StartGame(MinesweeperGame *game, Point startPoint)
{
    if (IS_POINT_IN_BOARD(game, startPoint))
    {
        game->startTime = clock();
        // TODO: Reveal cells at `startPoint`
    }
    return false;
}

bool HasWonGame(const MinesweeperGame *game)
{
    // TODO: Implement checking if the current board is a winning board
}

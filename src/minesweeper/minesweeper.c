#include "minesweeper.h"

void InitGame(MinesweeperGame *game, unsigned amountMines)
{
    game->mines = CreateBoard(game->width, game->height);
    game->flags = CreateBoard(game->width, game->height);
    game->revealed = CreateBoard(game->width, game->height);
    for (int i = 0; i < 10; i++)
        game->numbers[i] = CreateBoard(game->width, game->height);
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
    if (InBoard(game, startPoint))
    {
        game->startTime = clock();
        
    }
    return false;
}

bool HasWonGame(const MinesweeperGame *game)
{
    // TODO: Implement checking if the current board is a winning board
}

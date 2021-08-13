#include "state_handler.h"

void ChangeGameState(GameStruct *gameStruct, GameState newState)
{
    GameState oldState = gameStruct->gameState;
    gameStruct->gameState = newState;
    OnGameStateChange(gameStruct, oldState, newState);
}

void OnGameStateChange(GameStruct *gameStruct, GameState oldState, GameState newState)
{
    if (newState == GS_ALIVE)
    {
        gettimeofday(&(gameStruct->startTime), 0);
    }

    if (newState == GS_DEAD || newState == GS_WON)
    {
        gettimeofday(&(gameStruct->endTime), 0);
    }

    if (newState == GS_WON)
    {
        // Set all mines to flags
        for (INDEX_T i = 0; i < gameStruct->game->amountCells; i++)
        {
            if (IsBoardMarkedAtIndex(gameStruct->game->mines, i))
            {
                MarkBoardAtIndex(gameStruct->game->flags, i);
            }
        }
    }
}

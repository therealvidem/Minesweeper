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
        if (!gettime(&(gameStruct->startTime)))
        {
            TraceLog(LOG_WARNING, "Could not set the time using gettime()");
        }
    }

    if (newState == GS_DEAD || newState == GS_WON)
    {
        if (!gettime(&(gameStruct->endTime)))
        {
            TraceLog(LOG_WARNING, "Could not set the time using gettime()");
        }
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
            else
            {
                MarkBoardAtIndex(gameStruct->game->opened, i);
            }
        }
    }
}

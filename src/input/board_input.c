#include "board_input.h"

bool GetPointFromPosition(GameStruct *gameStruct, Vector2 position, Point *outPoint)
{
    int x, y;
    x = (int)((position.x - gameStruct->boardOffset.x)/(gameStruct->boardScale.x*gameStruct->textures->boardTileSize.x));
    y = (int)((position.y - gameStruct->boardOffset.y)/(gameStruct->boardScale.y*gameStruct->textures->boardTileSize.y));
#ifndef NDEBUG
    TraceLog(LOG_DEBUG, "Got clickedPoint (%d, %d) from mouse pos (%f, %f)", x, y, position.x, position.y);
#endif
    if ((x >= 0 && (INDEX_T)x < gameStruct->game->width)
     && (y >= 0 && (INDEX_T)y < gameStruct->game->height))
    {
        outPoint->x = (INDEX_T)x;
        outPoint->y = (INDEX_T)y;
        return true;
    }
    else
    {
        return false;
    }
}

bool HandleLeftClickCell(GameStruct *gameStruct)
{
    Vector2 mousePosition = GetMousePosition();
    Point clickedPoint;
    bool foundPoint = GetPointFromPosition(gameStruct, mousePosition, &clickedPoint);
    if (foundPoint && !IsPointFlag(gameStruct->game, clickedPoint))
    {
        CellType openedCellType = OpenSingleCell(gameStruct->game, clickedPoint);
#ifndef NDEBUG
        TraceLog(LOG_DEBUG, "Opened cell of type '%d'", openedCellType);
#endif

        switch(openedCellType)
        {
        case CT_MINE:
            {
                gameStruct->gameState = GS_DEAD;
            } break;
        default:
            break;
        }

        gameStruct->lastOpenedPoint = clickedPoint;
        return true;
    }
    return false;
}

void HandleRightClickCell(GameStruct *gameStruct)
{
    Vector2 mousePosition = GetMousePosition();
    Point clickedPoint;
    bool foundPoint = GetPointFromPosition(gameStruct, mousePosition, &clickedPoint);
    if (foundPoint)
    {
        FlagCell(gameStruct->game, clickedPoint);
    }
}

void HandleBoardInput(GameStruct *gameStruct)
{
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        switch (gameStruct->gameState)
        {
        case GS_INITIAL:
            {
                if (HandleLeftClickCell(gameStruct))
                {
                    gameStruct->gameState = GS_ALIVE;
                    StartGame(gameStruct->game, GetRandomValue, gameStruct->amountMines, gameStruct->lastOpenedPoint);
                }
            } break;
        case GS_ALIVE:
            {
                HandleLeftClickCell(gameStruct);
            } break;
        default:
            break;
        }
#ifndef NDEBUG
        TraceLog(LOG_DEBUG, "mines amountMarked: %d", gameStruct->game->mines.amountMarked);
        TraceLog(LOG_DEBUG, "flags amountMarked: %d", gameStruct->game->flags.amountMarked);
        TraceLog(LOG_DEBUG, "numbers amountMarked: %d", gameStruct->game->numbers.amountMarked);
        TraceLog(LOG_DEBUG, "opened amountMarked: %d", gameStruct->game->opened.amountMarked);
#endif
    }
    else if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON))
    {
        switch (gameStruct->gameState)
        {
        case GS_INITIAL:
            {
                HandleRightClickCell(gameStruct);
            } break;
        case GS_ALIVE:
            {
                HandleRightClickCell(gameStruct);
            } break;
        default:
            break;
        }
#ifndef NDEBUG
        TraceLog(LOG_DEBUG, "mines amountMarked: %d", gameStruct->game->mines.amountMarked);
        TraceLog(LOG_DEBUG, "flags amountMarked: %d", gameStruct->game->flags.amountMarked);
        TraceLog(LOG_DEBUG, "numbers amountMarked: %d", gameStruct->game->numbers.amountMarked);
        TraceLog(LOG_DEBUG, "opened amountMarked: %d", gameStruct->game->opened.amountMarked);
#endif
    }
    // Restart the game
    else if (IsKeyPressed(KEY_R))
    {
        gameStruct->gameState = GS_INITIAL;
        ResetGame(gameStruct->game);
#ifndef NDEBUG
        TraceLog(LOG_DEBUG, "mines amountMarked: %d", gameStruct->game->mines.amountMarked);
        TraceLog(LOG_DEBUG, "flags amountMarked: %d", gameStruct->game->flags.amountMarked);
        TraceLog(LOG_DEBUG, "numbers amountMarked: %d", gameStruct->game->numbers.amountMarked);
        TraceLog(LOG_DEBUG, "opened amountMarked: %d", gameStruct->game->opened.amountMarked);
#endif
    }
#ifndef NDEBUG
    // Win the game automatically
    else if (IsKeyPressed(KEY_W))
    {
        for (INDEX_T i = 0; i < gameStruct->game->amountCells; i++)
        {
            if (!IsBoardMarkedAtIndex(&(gameStruct->game->mines), i))
            {
                UnmarkBoardAtIndex(&(gameStruct->game->flags), i);
                MarkBoardAtIndex(&(gameStruct->game->opened), i);
            }
        }
#ifndef NDEBUG
        TraceLog(LOG_DEBUG, "mines amountMarked: %d", gameStruct->game->mines.amountMarked);
        TraceLog(LOG_DEBUG, "flags amountMarked: %d", gameStruct->game->flags.amountMarked);
        TraceLog(LOG_DEBUG, "numbers amountMarked: %d", gameStruct->game->numbers.amountMarked);
        TraceLog(LOG_DEBUG, "opened amountMarked: %d", gameStruct->game->opened.amountMarked);
#endif
    }
#endif
}

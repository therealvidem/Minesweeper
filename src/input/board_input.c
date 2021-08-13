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
    if (foundPoint 
     && !IsPointFlag(gameStruct->game, clickedPoint)
     && !IsPointOpen(gameStruct->game, clickedPoint))
    {
        if (IsPointEmpty(gameStruct->game, clickedPoint) && !IsPointMine(gameStruct->game, clickedPoint))
        {
            FloodFiller *ff = CreateFloodFiller(gameStruct->game, clickedPoint);
    
#ifndef NDEBUG
            TraceLog(LOG_DEBUG, "Flood fill started");
#endif

            bool opening = true;
            while (opening)
            {
                CellReturnStatus openedCellType = IterateFloodFiller(ff);
                switch (openedCellType)
                {
                case CRS_FLOODFILL_STOPPED:
                    {
                        opening = false;
#ifndef NDEBUG
                        TraceLog(LOG_DEBUG, "Flood fill stopped");
#endif
                        FreeFloodFiller(ff);
                        ff = NULL;
                    } break;
                case CRS_MINE:
                    {
                        ChangeGameState(gameStruct, GS_DEAD);
                        opening = false;
                    } break;
                default:
                    {

                    } break;
                }
            }

            FreeFloodFiller(ff);
            ff = NULL;
        }
        else
        {
            CellReturnStatus openedCellType = OpenSingleCell(gameStruct->game, clickedPoint);
#ifndef NDEBUG
            TraceLog(LOG_DEBUG, "Opened cell of type '%d'", openedCellType);
#endif

            switch(openedCellType)
            {
            case CRS_MINE:
                {
                    ChangeGameState(gameStruct, GS_DEAD);
                } break;
            default:
                break;
            }

            gameStruct->lastOpenedPoint = clickedPoint;
        }
        
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
                Vector2 mousePosition = GetMousePosition();
                Point clickedPoint;
                bool foundPoint = GetPointFromPosition(gameStruct, mousePosition, &clickedPoint);
                if (foundPoint && !IsPointFlag(gameStruct->game, clickedPoint))
                {
                    StartGame(gameStruct->game, GetRandomValue, gameStruct->amountMines, clickedPoint);
                    HandleLeftClickCell(gameStruct);
                    ChangeGameState(gameStruct, GS_ALIVE);
                }
            } break;
        case GS_ALIVE:
            {
                HandleLeftClickCell(gameStruct);
            } break;
        default:
            break;
        }
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
    }
    // Restart the game
    else if (IsKeyPressed(KEY_R))
    {
        ChangeGameState(gameStruct, GS_INITIAL);
        ResetGame(gameStruct->game);
    }
#ifndef NDEBUG
    // Win the game automatically
    else if (IsKeyPressed(KEY_W))
    {
        for (INDEX_T i = 0; i < gameStruct->game->amountCells; i++)
        {
            if (!IsBoardMarkedAtIndex(gameStruct->game->mines, i))
            {
                UnmarkBoardAtIndex(gameStruct->game->flags, i);
                MarkBoardAtIndex(gameStruct->game->opened, i);
            }
        }
    }
#endif
}

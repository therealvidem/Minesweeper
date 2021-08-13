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

void ExecuteFloodFill(GameStruct *gameStruct, Point point)
{
    CellOpeningQueue *ff = CreateCellOpeningQueue(gameStruct->game, point);
    
#ifndef NDEBUG
    TraceLog(LOG_DEBUG, "Flood fill started");
#endif

    if (!IsPointQueueEmpty(ff->queue))
    {
        bool opening = true;
        while (opening)
        {
            if (!IsPointQueueEmpty(ff->queue))
            {
                gameStruct->lastOpenedPoint = PeekPointQueue(ff->queue);
            }
            CellReturnStatus openedCellType = IterateFloodFiller(ff);
            switch (openedCellType)
            {
            case CRS_OPEN_QUEUE_STOPPED:
                {
                    opening = false;
#ifndef NDEBUG
                    TraceLog(LOG_DEBUG, "Flood fill stopped");
#endif
                } break;
            case CRS_MINE:
                {
                    gameStruct->mineHitPoint = point;
                    ChangeGameState(gameStruct, GS_DEAD);
                    opening = false;
                } break;
            default:
                break;
            }
        }
    }

    FreeCellOpeningQueue(ff);
    ff = NULL;
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
            ExecuteFloodFill(gameStruct, clickedPoint);
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
                    gameStruct->mineHitPoint = clickedPoint;
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

void HandleMiddleClickCell(GameStruct *gameStruct)
{
    Vector2 mousePosition = GetMousePosition();
    Point clickedPoint;
    bool foundPoint = GetPointFromPosition(gameStruct, mousePosition, &clickedPoint);
    if (foundPoint)
    {
        CellOpeningQueue *chordQueue = ChordCell(gameStruct->game, clickedPoint);
        if (chordQueue)
        {

#ifndef NDEBUG
            TraceLog(LOG_DEBUG, "Chording started");
#endif

            bool opening = true;
            while (opening)
            {
                if (!IsPointQueueEmpty(chordQueue->queue))
                {
                    gameStruct->lastOpenedPoint = PeekPointQueue(chordQueue->queue);
                }
                CellReturnStatus openedCellType = IterateChord(chordQueue);
                switch (openedCellType)
                {
                case CRS_OPEN_QUEUE_STOPPED:
                    {
                        opening = false;
#ifndef NDEBUG
                        TraceLog(LOG_DEBUG, "Chording stopped");
#endif
                    } break;
                case CRS_MINE:
                    {
                        gameStruct->mineHitPoint = clickedPoint;
                        ChangeGameState(gameStruct, GS_DEAD);
                        opening = false;
                    } break;
                case CRS_0:
                    {
                        TraceLog(LOG_DEBUG, "Opened a 0 at (%d, %d), preparing to flood fill", gameStruct->lastOpenedPoint.x, gameStruct->lastOpenedPoint.y);
                        UnmarkBoardAtPoint(gameStruct->game->opened, gameStruct->lastOpenedPoint);
                        ExecuteFloodFill(gameStruct, gameStruct->lastOpenedPoint);
                    } break;
                default:
                    break;
                }
            }

            FreeCellOpeningQueue(chordQueue);
            chordQueue = NULL;
        }
#ifndef NDEBUG
        else
        {
            TraceLog(LOG_DEBUG, "Cannot chord (%d, %d)", clickedPoint.x, clickedPoint.y);
        }
#endif
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
        case GS_ALIVE:
            {
                HandleRightClickCell(gameStruct);
            } break;
        default:
            break;
        }
    }
    else if (IsMouseButtonReleased(MOUSE_MIDDLE_BUTTON))
    {
        switch (gameStruct->gameState)
        {
        case GS_ALIVE:
            {
                HandleMiddleClickCell(gameStruct);
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

#include "board_graphics.h"

const Vector2 origin = {
    .x = 0,
    .y = 0,
};

void DrawBoard(
    const Board *board,
    const Textures *textures,
    BoardTile markedTile,
    BoardTile unmarkedTile,
    Vector2 position,
    Vector2 scale
)
{
    BoardTile tile;
    Point point;
    Rectangle destRect;
    INDEX_T amountCells = board->width * board->height;
    for (INDEX_T i = 0; i < amountCells; i++)
    {
        tile = IsBoardMarkedAtIndex(board, i) ? markedTile : unmarkedTile;
        point = GetPointFromIndex(board, i);
        destRect.x = position.x + (float)(point.x)*(scale.x*(textures->boardTileSize.x));
        destRect.y = position.y + (float)(point.y)*(scale.y*(textures->boardTileSize.y));
        destRect.width = scale.x*(textures->boardTileSize.x);
        destRect.height = scale.y*(textures->boardTileSize.y);

        DrawTexturePro(
            textures->boardTilset,
            textures->boardTileRecs[tile],
            destRect,
            origin,
            0.0f,
            WHITE
        );
        // DrawRectangle(
        //     destRect.x,
        //     destRect.y,
        //     destRect.width,
        //     destRect.height,
        //     RED
        // );
    }
}

Vector2 GetBoardDrawSize(const Board *board, const Textures *textures, Vector2 scale)
{
    return (Vector2){
        .x = (scale.x*((board->width)*(textures->boardTileSize.x))),
        .y = (scale.y*((board->height)*(textures->boardTileSize.y))),
    };
}

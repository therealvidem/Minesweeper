#include "board_graphics.h"

const Vector2 origin = {
    .x = 0,
    .y = 0,
};

Vector2 PointToDrawPosition(Point point, Vector2 offset, Vector2 scale, Vector2 boardTileSize)
{
    return (Vector2){
        .x = offset.x + (float)(point.x)*(scale.x*(boardTileSize.x)),
        .y = offset.y + (float)(point.y)*(scale.y*(boardTileSize.y)),
    };
}

Rectangle GetDestRectFromPoint(Point point, Vector2 offset, Vector2 scale, Vector2 boardTileSize)
{
    return (Rectangle){
        .x = offset.x + (float)(point.x)*(scale.x*(boardTileSize.x)),
        .y = offset.y + (float)(point.y)*(scale.y*(boardTileSize.y)),
        .width = scale.x*(boardTileSize.x),
        .height = scale.y*(boardTileSize.y),
    };
}

void DrawBoard(
    const Board *board,
    const Textures *textures,
    const BoardTile *tiles,
    size_t numTiles,
    Vector2 offset,
    Vector2 scale
)
{
    BoardTile tile;
    Point point;
    ARRAY_T cellValue;
    for (INDEX_T i = 0; i < board->amountCells; i++)
    {
        point = GetPointFromIndex(board, i);
        cellValue = board->_arr[i];

        if (cellValue < (int)numTiles)
        {
            tile = tiles[cellValue];
        }
        else
        {
            tile = tiles[0];
        }

        DrawTexturePro(
            textures->boardTilset,
            textures->boardTileRecs[tile],
            GetDestRectFromPoint(point, offset, scale, textures->boardTileSize),
            origin,
            0.0f,
            WHITE
        );
    }
}

void DrawMarkedBoard(
    const Board *board,
    const Textures *textures,
    BoardTile unmarkedTile,
    BoardTile markedTile,
    Vector2 offset,
    Vector2 scale
)
{
    BoardTile tiles[2] = { unmarkedTile, markedTile };
    DrawBoard(
        board,
        textures,
        tiles,
        2,
        offset,
        scale
    );
    // BoardTile tile;
    // Point point;
    // for (INDEX_T i = 0; i < board->amountCells; i++)
    // {
    //     point = GetPointFromIndex(board, i);
    //     tile = IsBoardMarkedAtIndex(board, i) ? markedTile : unmarkedTile;

    //     DrawTexturePro(
    //         textures->boardTilset,
    //         textures->boardTileRecs[tile],
    //         GetDestRectFromPoint(point, offset, scale, textures->boardTileSize),
    //         origin,
    //         0.0f,
    //         WHITE
    //     );
    // }
}

void DrawCell(const Textures *textures, Point cellPoint, BoardTile cellTile, Vector2 offset, Vector2 scale)
{
    DrawTexturePro(
        textures->boardTilset,
        textures->boardTileRecs[cellTile],
        GetDestRectFromPoint(cellPoint, offset, scale, textures->boardTileSize),
        origin,
        0.0f,
        WHITE
    );
}

Vector2 GetBoardDrawSize(INDEX_T boardWidth, INDEX_T boardHeight, const Textures *textures, Vector2 scale)
{
    return (Vector2){
        .x = (scale.x*(boardWidth*(textures->boardTileSize.x))),
        .y = (scale.y*(boardHeight*(textures->boardTileSize.y))),
    };
}

#include "include/point.h"

bool InBounds(Point point, INDEX_T width, INDEX_T height)
{
    return point.x < width && point.y < height;
}

PointDelta GetPointDifference(Point lhs, Point rhs)
{
    return (PointDelta){
        .x = (int)lhs.x - (int)rhs.x,
        .y = (int)lhs.y - (int)rhs.y,
    };
}

bool ArePointNeighbors(Point p1, Point p2)
{
    PointDelta difference = GetPointDifference(p1, p2);
    return (difference.x >= -1 && difference.x <= 1)
        && (difference.y >= -1 && difference.y <= 1);
}

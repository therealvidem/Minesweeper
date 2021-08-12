#include "include/point.h"

bool InBounds(Point point, INDEX_T width, INDEX_T height)
{
    return point.x < width && point.y < height;
}

bool ArePointNeighbors(Point p1, Point p2)
{
    int deltaX = (int)p1.x - (int)p2.x;
    int deltaY = (int)p1.y - (int)p2.y;
    
    return (deltaX >= -1 && deltaX <= 1)
        && (deltaY >= -1 && deltaY <= 1);
}

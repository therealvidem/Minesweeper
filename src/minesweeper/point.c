#include "point.h"

int InBounds(Point point, INDEX_T width, INDEX_T height)
{
    return point.x >= 0 && point.x < width
        && point.y >= 0 && point.y < height;
}

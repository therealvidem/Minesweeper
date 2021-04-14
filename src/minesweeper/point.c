#include "point.h"

int InBounds(Point point, POINT_T width, POINT_T height)
{
    return point.x >= 0 && point.x < width
        && point.y >= 0 && point.y < height;
}

#include "Circle.h"
#include <cmath>

bool
Circle::isOverlap(Circle *circle_1, Circle *circle_2)
{
    int length = circle_1->r + circle_2->r;
    int distance_square = (circle_1->x - circle_2->x) * (circle_1->x - circle_2->x)
                            + (circle_1->y - circle_2->y) * (circle_1->y - circle_2->y);

    if(length * length >= distance_square)
        return true;

    return false;
}

double
Circle::Distance(Circle* a, Circle* b)
{
    double dx = b->x - a->x, dy = b->y - a->y;
    return sqrt(dx * dx + dy * dy);
}

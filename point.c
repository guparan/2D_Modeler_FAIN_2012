#include "point.h"

Point point(int x, int y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}


int point_sontEgaux(Point p1, Point p2)
{
    return (p1.x == p2.x && p1.y == p1.y);
}

int point_estSuperieur(Point p1, Point p2)
{
    return (p1.x > p2.x || p1.y > p2.y);
}

int point_estInferieur(Point p1, Point p2)
{
    return (p1.x < p2.x || p1.y < p2.y);
}

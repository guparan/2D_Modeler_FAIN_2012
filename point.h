#ifndef POINT_H
#define POINT_H

typedef struct point
{
    int x;
    int y;
} Point;


Point point(int x, int y);
int point_egaux(Point p1, Point p2);

#endif

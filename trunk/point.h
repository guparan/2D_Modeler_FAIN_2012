#ifndef POINT_H
#define POINT_H

typedef struct point
{
    int x;
    int y;
} Point;


Point point(int x, int y);
int point_sontEgaux(Point p1, Point p2);
int point_estSuperieur(Point p1, Point p2);
int point_estInferieur(Point p1, Point p2);
double point_distance(Point p1, Point p2);

#endif

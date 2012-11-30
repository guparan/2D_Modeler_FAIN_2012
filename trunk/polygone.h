#include "primitives.h"
#include "point.h"

#ifndef POLYGONE_H
#define POLYGONE_H

typedef struct {
    Point sommets[64];
    Point pmin;
    Point pmax;
} Polygone;

void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Point pmin, Point pmax, Couleur couleur);

#endif

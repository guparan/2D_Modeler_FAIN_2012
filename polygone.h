#include "primitives.h"
#include "point.h"

#ifndef FAIN_TP1_polygone_h
#define FAIN_TP1_polygone_h

typedef struct {
    Point sommets[64];
    Point pmin;
    Point pmax;
} Polygone;

void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Point pmin, Point pmax, Couleur couleur);

#endif

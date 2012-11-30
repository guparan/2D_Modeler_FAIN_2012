#include "primitives.h"
#include "point.h"
#include "liste.h"

#ifndef POLYGONE_H
#define POLYGONE_H

typedef struct {
    Liste sommets;
    Point pmin;
    Point pmax;
    int ferme;
} Polygone;

void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Point pmin, Point pmax, Couleur couleur);

#endif

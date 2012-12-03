#include "primitives.h"
#include "point.h"
#include "liste.h"

#ifndef POLYGONE_H
#define POLYGONE_H

typedef struct {
    Liste* sommets;
    Point pmin;
    Point pmax;
    int ferme;
} Polygone;

Polygone* polygone_creer();
void polygone_ajouterSommet(Polygone* polygone, Point p);

void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Polygone *p, Couleur couleur);
void polygone_remplirScanline2(Polygone* p, Couleur couleur);
void polygone_detruire(Polygone *p);

#endif

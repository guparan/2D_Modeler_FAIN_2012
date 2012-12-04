
#ifndef FAIN_droite_h
#define FAIN_droite_h

#include "point.h"

/* Structure définissant une droite d'équation ax + by + c = 0 */
typedef struct droite {
    int a;
    int b;
    int c;
} Droite;

Droite droite_obtenirEquation(Point p1, Point p2);
double droite_distancePointDroite(Point p, Droite d);


#endif

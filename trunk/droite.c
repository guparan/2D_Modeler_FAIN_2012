//
//  droite.c
//  FAIN
//
//  Created by Lucas Saurel on 04/12/12.
//  Copyright (c) 2012 Lucas Saurel. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "droite.h"

Droite droite_obtenirEquation(Point p1, Point p2)
{
    Droite d;
    d.a = p2.y - p1.y;
    d.b = p1.x - p2.x;
    d.c = -d.b * p1.y - d.a * p1.x;
    return d;
}


double droite_distancePointDroite(Point p, Droite d)
{
    double numerateur = abs(d.a*p.x + d.b*p.y + d.c);
    double denominateur = sqrt(pow(d.a,2) + pow(d.b,2));
    return (numerateur/denominateur);
}

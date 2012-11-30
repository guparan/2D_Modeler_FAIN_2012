#include <stdio.h>
#include "polygone.h"


void polygone_remplirGraine(Point pgraine)
{
    int xgraine = pgraine.x, ygraine = pgraine.y;
    Couleur c = val_point(xgraine, ygraine);
    
    if(c == BLANC || c == ROUGE ) return;
    
    if( xgraine < 0 || xgraine > hauteur_ecran() || ygraine < 0 || ygraine > largeur_ecran() )
    {
        return;
    }
    
    change_point(xgraine,ygraine,ROUGE);
    polygone_remplirGraine(point(xgraine-1, ygraine));
    polygone_remplirGraine(point(xgraine, ygraine-1));
    polygone_remplirGraine(point(xgraine+1, ygraine));
    polygone_remplirGraine(point(xgraine, ygraine+1));
}


void polygone_remplirScanline(Point pmin, Point pmax)
{
    int xmin = pmin.x, xmax = pmax.x, ymin = pmin.y, ymax = pmax.y;
    int x, y;
    
    for (y = ymin; y < ymax; y++)
    {
        for (x = xmin; x < xmax; x++) {
            
        }
    }
}
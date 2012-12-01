#include <stdio.h>
#include "polygone.h"


Polygone* polygone_creer()
{
    Polygone* p = (Polygone*) malloc(sizeof(Polygone));
    p->sommets = liste_creer();
    p->ferme = faux;
    p->pmin = point(-1, -1);
    p->pmax = point(-1, -1);
    return p;
}

void polygone_ajouterSommet(Polygone* polygone, Point p)
{
    if(point_estSuperieur(p, polygone->pmax) || point_sontEgaux(polygone->pmax, point(-1,-1)))
    {
        polygone->pmax = p;
    }
    if(point_estInferieur(p, polygone->pmin) || point_sontEgaux(polygone->pmin, point(-1,-1)))
    {
        polygone->pmin = p;
    }
    liste_insere(polygone->sommets, p);
}


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


void polygone_remplirScanline(Polygone* p, Couleur couleur)
{
    int xmin = p->pmin.x, xmax = p->pmax.x, ymin = p->pmin.y, ymax = p->pmax.y;
    int x, y;
    int interieur = 0;

    if(!p->ferme) return;
    
    for (y = ymin; y < ymax; y++)
    {
        for (x = xmin; x < xmax; x++)
        {
            if (val_point(x, y) == NOIR) {
                if (interieur) change_point(x, x, couleur);
            }
            else if (val_point(x, y) == BLANC) {
                if (val_point(x+1, y) == NOIR) {
                    interieur = 1;
                }
            }
        }
    }
}

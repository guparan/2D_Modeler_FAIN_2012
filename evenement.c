
#include <stdio.h>
#include "primitives.h"
#include "polygone.h"
#include "segment.h"
#include "evenement.h"
#include "point.h"


void evenement_boutonDroit(int x, int y, int fin_click)
{
    static int x0,y0;
    if(fin_click) printf("fin"); else printf("debut");
    printf(" appui bouton du milieu de la souris\n");
    if(fin_click) {
        segment_segmentBresenham(point(x0,y0), point(x,y), BLANC);
    }
    else {
        x0=x; y0=y;
    }
}


void evenement_boutonMilieu(int x, int y, int fin_click)
{
    if(fin_click) polygone_remplirGraine(point(x, y));
}


void evenement_clavier(unsigned char touche, int x, int y)
{
    printf("touche %c appuyee\n", touche);
}

int main(int nargs, char **args)
{
    initPrimitives(nargs,args);
    return 0;
}

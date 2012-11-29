
#include <stdio.h>
#include "modeleur.h"
#include "polygone.h"
#include "segment.h"
#include "evenement.h"


void evenement_boutonDroit(int x, int y, int fin_click)
{
    if(fin_click) polygone_remplirGraine(x, x);
}


void evenement_boutonMilieu(int x, int y, int fin_click)
{
    static int x0,y0;
    if(fin_click) printf("fin"); else printf("debut");
    printf(" appui bouton du milieu de la souris\n");
    if(fin_click) {
        segment_segmentBresenham(x0,y0,x,y);
    }
    else {
        x0=x; y0=y;
    }
}


void evenement_clavier(unsigned char touche, int x, int y)
{
    printf("touche %c appuyee\n", touche);
}

int main(int nargs, char **args)
{
    main_Modeleurlib(nargs,args);
    return 0;
}

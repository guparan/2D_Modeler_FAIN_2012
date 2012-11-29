//
//  actions.c
//  FAIN-TP1
//
//  Created by Lucas Saurel on 29/11/12.
//  Copyright (c) 2012 Lucas Saurel. All rights reserved.
//

#include <stdio.h>
#include "modeleurlib.h"


void action_bouton_droit(int x, int y, int fin_click)
{
    if(fin_click) remplir(x,y);
}


void action_bouton_milieu(int x, int y, int fin_click)
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


void action_clavier(unsigned char touche, int x, int y)
{
    printf("touche %c appuyee\n", touche);
}

int main(int nargs, char **args)
{
    main_Modeleurlib(nargs,args);
    return 0;
}

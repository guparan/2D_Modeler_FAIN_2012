
#include <stdio.h>
#include "modeleurlib.h"


void remplir(int xgraine, int ygraine)
{
    couleur c = val_point(xgraine, ygraine);
    
    if(c == BLANC || c == ROUGE ) return;
    
    if( xgraine < 0 || xgraine > hauteur_ecran() || ygraine < 0 || ygraine > largeur_ecran() )
    {
        return;
    }
    
    change_point(xgraine,ygraine,ROUGE);
    remplir(xgraine-1, ygraine);
    remplir(xgraine, ygraine-1);
    remplir(xgraine+1, ygraine);
    remplir(xgraine, ygraine+1);
}

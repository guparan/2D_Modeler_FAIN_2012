//
//  polygone.c
//  FAIN-TP1
//
//  Created by Lucas Saurel on 29/11/12.
//  Copyright (c) 2012 Lucas Saurel. All rights reserved.
//

#include <stdio.h>
#include "polygone.h"
#include "modeleur.h"


void polygone_remplirGraine(int xgraine, int ygraine)
{
    couleur c = val_point(xgraine, ygraine);
    
    if(c == BLANC || c == ROUGE ) return;
    
    if( xgraine < 0 || xgraine > hauteur_ecran() || ygraine < 0 || ygraine > largeur_ecran() )
    {
        return;
    }
    
    change_point(xgraine,ygraine,ROUGE);
    polygone_remplirGraine(xgraine-1, ygraine);
    polygone_remplirGraine(xgraine, ygraine-1);
    polygone_remplirGraine(xgraine+1, ygraine);
    polygone_remplirGraine(xgraine, ygraine+1);
}

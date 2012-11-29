//
//  evenement.h
//  FAIN-TP1
//
//  Created by Lucas Saurel on 29/11/12.
//  Copyright (c) 2012 Lucas Saurel. All rights reserved.
//

#ifndef FAIN_TP1_evenement_h
#define FAIN_TP1_evenement_h

/* Fonction executee deux fois lorsque que l'on appuie (fin_click=0)
 ou relache (fin_click=1) le bouton du milieu de la souris
 x et y representent les coordonnées du curseur de la souris */
void evenement_boutonMilieu(int x, int y, int fin_click);

/* Fonction executee deux fois lorsque que l'on appuie (fin_click=0)
 ou relache (fin_click=1) le bouton de droite de la souris
 x et y representent les coordonnées du curseur de la souris */
void evenement_boutonDroit(int x, int y, int fin_click);

/* Fonction executee lorsqu'on appuie sur une touche du clavier
 x et y representent les coordonnées du curseur de la souris
 les caractere touche correspond à la touche appuyee */
void evenement_clavier(unsigned char touche, int x,int y);

#endif

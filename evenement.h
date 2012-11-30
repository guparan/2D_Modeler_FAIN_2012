
#ifndef EVENEMENT_H
#define EVENEMENT_H


/* Fonction executee lorsqu'on appuie sur une touche du clavier
 x et y representent les coordonnées du curseur de la souris
 les caractere touche correspond à la touche appuyee */
void evenement_clavier(unsigned char touche, int x,int y);

void evenement_souris(int b,int s,int x,int y);

/* Fonction executee deux fois lorsque que l'on appuie (fin_click=0)
 ou relache (fin_click=1) le bouton du milieu de la souris
 x et y representent les coordonnées du curseur de la souris */
void evenement_boutonMilieu(int x, int y, int fin_click);

/* Fonction executee deux fois lorsque que l'on appuie (fin_click=0)
 ou relache (fin_click=1) le bouton de droite de la souris
 x et y representent les coordonnées du curseur de la souris */
void evenement_boutonDroit(int x, int y, int fin_click);

void evenement_boutonGauche(int x, int y, int fin_click);


#endif

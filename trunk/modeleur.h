
#ifndef MODELEUR_H
#define MODELEUR_H

#include <stdio.h>
#include <math.h>	

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>

#define MAXX 1024
#define MAXY 768

/* Noms des couleurs */
typedef enum {NOIR,BLANC,ROUGE,VERT,BLEU,JAUNE,MAGENTA,CYAN,GRIS} couleur;

/* Change la couleur d'un pixel */
void change_point(int x, int y, couleur c);

/* Renvoie la couleur d'un pixel */
couleur val_point(int x, int y);


/* Efface toute la fenetre */
void efface_tout(void);

/* Donne la largeur courante de la fenêtre
 les 1ere coordonnees des pixels de l'ecran
 vont de 0 a largeur_ecran()-1
 */
int largeur_ecran(void);

/* Donne la hauteur courante de la fenêtre
 les 2emes coordonnees des pixels de l'ecran
 vont de 0 a hauteur_ecran()-1
 */
int hauteur_ecran(void);

/* A mettre dans la fonction main */
int main_Modeleurlib(int nargs, char **args);


#endif

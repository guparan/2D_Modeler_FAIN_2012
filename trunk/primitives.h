
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>
#include <math.h>	

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <string.h>

#define MAXX 1920
#define MAXY 1080


/* Noms des couleurs */
typedef enum {NOIR,BLANC,ROUGE,VERT,BLEU,JAUNE,MAGENTA,CYAN,GRIS} Couleur;

/* Change la couleur d'un pixel */
void change_point(int x, int y, Couleur c);

/* Renvoie la couleur d'un pixel */
Couleur val_point(int x, int y);




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
int initPrimitives(int nargs, char **args);


#endif

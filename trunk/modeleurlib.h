
#ifndef MODELEURLIB_H
#define MODELEURLIB_H

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


void remplir(int xgraine, int ygraine);


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


/* Fonction executee deux fois lorsque que l'on appuie (fin_click=0)
   ou relache (fin_click=1) le bouton du milieu de la souris
   x et y representent les coordonnées du curseur de la souris */
void action_bouton_milieu(int x, int y, int fin_click);

/* Fonction executee deux fois lorsque que l'on appuie (fin_click=0)
   ou relache (fin_click=1) le bouton de droite de la souris
   x et y representent les coordonnées du curseur de la souris */
void action_bouton_droit(int x, int y, int fin_click);

/* Fonction executee lorsqu'on appuie sur une touche du clavier
    x et y representent les coordonnées du curseur de la souris
    les caractere touche correspond à la touche appuyee */
void action_clavier(unsigned char touche, int x,int y);


/* Détermine dans quel octant le segment se trouve et demande le tracé à la fonction tracer_segment */
void segment_segmentBresenham(int xA,int yA,int xB,int yB);
/* Trace un segment dans un octant donné */
void segment_tracerSegment(int xA,int yA,int xB,int yB, int octant);
void segment_tracerSegmentVertical(int xA, int yA, int yB);
void segment_tracerSegmentHorizontal(int yA, int xA, int xB);

#endif

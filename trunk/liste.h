
#ifndef LISTES_h
#define LISTES_h

#include "point.h"

typedef enum {false, true} bool;

typedef struct maillon {
	Point point;
    struct maillon *suivant;
} Maillon;

typedef struct liste {
    Maillon *tete;
    Maillon *queue;
} Liste;

// Cree une liste a partir d'un point
Liste* liste_creer ();

// Ajoute un element en tete de liste et retourne la liste
//void liste_ajout(Liste *l, Point p);

// Insere un élément à la fin de la liste et retourne la liste
void liste_insere(Liste* l, Point p);

// Retourne la taille d'une liste
int liste_taille(Liste *l);

// Retourne 1 si l'element en paramètre est dans la liste, 0 sinon
bool liste_appartient(Point p, Liste *l);

// Concatène l2 à la suite de l1
Liste *liste_concat(Liste *l1, Liste *l2);

// Retourne la position d'un élément dans une liste (0 si absent de la liste, 1 si premier de la liste, ...)
int liste_position(Point p, Liste* l);


#endif

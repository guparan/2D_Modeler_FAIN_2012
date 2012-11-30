
#ifndef LISTES_h
#define LISTES_h

#include "point.h"

typedef struct maillon *Liste;
struct maillon {
	Point point;
	Liste suivant;
};

// Ajoute un element en tete de liste et retourne la liste
Liste liste_ajout (Liste l, Point nvelt);

// Insere un élément à la fin de la liste et retourne la liste
Liste liste_insere(Liste l, Point e);

// Retourne 1 si l'element en paramètre est dans la liste, 0 sinon
int liste_appartient(Point x, Liste l);

// Concatène l2 à la suite de l1
void liste_concat(Liste *l1, Liste l2);

// Retourne la position d'un élément dans une liste (0 si absent de la liste, 1 si premier de la liste, ...)
int liste_position(Point e, Liste l);

// Retourne 1 si l1 est incluse dans l2, 0 sinon
int liste_incluse(Liste l1, Liste l2);


#endif

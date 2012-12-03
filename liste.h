
#ifndef LISTES_h
#define LISTES_h

#include "point.h"

typedef enum {faux, vrai} booleen;

typedef struct maillon {
	Point point;
    struct maillon *suivant;
    struct maillon *precedent;
} Maillon;

typedef struct liste {
    Maillon *tete;
    Maillon *queue;
} Liste;

// Cree une liste a partir d'un point
Liste* liste_creer ();

// Detruit une liste (libere la memoire)
void liste_detruireListe(Liste* l);
void liste_detruireListeMaillons(Maillon* m);

// Supprime un maillon par comparaisons successives
void liste_supprimer(Liste* l, Maillon* m);

// Supprime directement l'élement d'indice 'rang' (plus rapide)
void liste_supprimerRang(Liste* l, int rang);

booleen liste_estVide(Liste* l);

// Insere un élément à la fin de la liste et retourne la liste
void liste_ajouter(Liste* l, Point p);

// Retourne la taille d'une liste
int liste_taille(Liste *l);

// Retourne 1 si l'element en paramètre est dans la liste, 0 sinon
booleen liste_appartient(Point p, Liste *l);

// Concatène l2 à la suite de l1
Liste *liste_concat(Liste *l1, Liste *l2);

// Retourne la position d'un élément dans une liste (0 si absent de la liste, 1 si premier de la liste, ...)
int liste_position(Point p, Liste* l);


#endif

#include "primitives.h"
#include "point.h"
#include "liste.h"

#ifndef POLYGONE_H
#define POLYGONE_H

typedef struct {
    Liste* sommets;
    Point pmin;
    Point pmax;
    Maillon* pointCourant;
    int ferme;
} Polygone;

/* Creation et destruction d'un polygone */
Polygone* polygone_creer();
void polygone_detruire(Polygone *p);

/* Ajout, deplacement et suppression de sommets */
void polygone_ajouterSommet(Polygone* polygone, Point p, int liaison);
void polygone_insererSommet(Polygone *polygone, Point p, Point suivant);
void polygone_supprimerSommet(Polygone *polygone, Point p);
void polygone_deplacerSommet(Polygone *polygone, Point p, Point direction);

/* Remplissage d'un polygone */
void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Polygone *p, Couleur couleur);
void polygone_remplirScanline2(Polygone* p, Couleur couleur);

/* Recherche d'un point dans un polygone */
int polygone_rang(Polygone *polygone, Point p);
Maillon* polygone_sommet(Polygone *polygone, Point p);

/* Redessine l'ensemble du polygone, si clear=1 le dessin est d'abord efface */
void polygone_dessiner(Polygone* p, int clear);


/* Mode Vertex */
Point polygone_sommetLePlusProche(Polygone *polygone, Point p);
void polygone_selectionneSommetSuivant(Polygone* polygone);
void polygone_selectionneSommetPrecedent(Polygone* polygone);
void polygone_deselectionneSommet(Polygone* polygone);

/* Mode Edge */
void polygone_selectionneAreteSuivante(Polygone* polygone);
void polygone_selectionneAretePrecedente(Polygone* polygone);

/* Remplissage d'un polygone */
void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Polygone *p, Couleur couleur);
void polygone_remplirScanline2(Polygone* p, Couleur couleur);

/* Mode Edge */
/* Retourne le sommet (maillon) de départ du segment le plus proche d'un point */
Maillon* polygone_segmentLePlusProche(Polygone *polygone, Point p);
void polygone_deselectionneArete(Polygone* polygone);
void polygone_selectionneAreteSuivante(Polygone* polygone);
void polygone_selectionneAretePrecedente(Polygone* polygone);

#endif

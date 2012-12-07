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

Polygone* polygone_creer();
void polygone_detruire(Polygone *p);
void polygone_ajouterSommet(Polygone* polygone, Point p, int liaison);
void polygone_insererSommet(Polygone *polygone, Point p, Point suivant);
void polygone_supprimerSommet(Polygone *polygone, Point p);

int polygone_rang(Polygone *polygone, Point p);
Maillon* polygone_sommet(Polygone *polygone, Point p);

void polygone_deplacerSommet(Polygone *polygone, Point p, Point direction);

Point polygone_sommetLePlusProche(Polygone *polygone, Point p);

/* Retourne le sommet de départ du segment le plus proche d'un point */
Maillon* polygone_segmentLePlusProche(Polygone *polygone, Point p);

void polygone_dessiner(Polygone* p, int clear);

/* Mode Vertex */
void polygone_selectionneSommetSuivant(Polygone* polygone);
void polygone_selectionneSommetPrecedent(Polygone* polygone);
void polygone_deselectionne(Polygone* polygone);

/* Mode Edge */
void polygone_selectionneAreteSuivante(Polygone* polygone);
void polygone_selectionneAretePrecedente(Polygone* polygone);

/* Remplissage d'un polygone */
void polygone_remplirGraine(Point pgraine);
void polygone_remplirScanline(Polygone *p, Couleur couleur);
void polygone_remplirScanline2(Polygone* p, Couleur couleur);

#endif

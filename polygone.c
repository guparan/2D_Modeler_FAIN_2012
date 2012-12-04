#include <stdio.h>
#include "polygone.h"
#include "segment.h"
#include "primitives.h"
#include "droite.h"

Polygone* polygone_creer()
{
    Polygone* p = (Polygone*) malloc(sizeof(Polygone));
    p->sommets = liste_creer();
    p->ferme = faux;
    p->pmin = point(-1, -1);
    p->pmax = point(-1, -1);
    p->pointCourant = NULL;
    return p;
}


void polygone_detruire(Polygone *p)
{
    if (p) liste_detruireListe(p->sommets);
    free(p);
}


void polygone_ajouterSommet(Polygone* polygone, Point p, int liaison)
{
    if(point_sontEgaux(polygone->pmax, point(-1,-1))) // initialisation
    {
        polygone->pmin = p;
        polygone->pmax = p;
    }
    else
    {
        if(p.x > polygone->pmax.x) polygone->pmax.x = p.x + 1;
        if(p.x < polygone->pmin.x) polygone->pmin.x = p.x - 1;
        if(p.y > polygone->pmax.y) polygone->pmax.y = p.y + 1;
        if(p.y < polygone->pmin.y) polygone->pmin.y = p.y - 1;
    }

    /* Ajout du sommet dans la vue */
    change_point(p.x,p.y,JAUNE);

    /* Tracé du segment si demandé */
//    printf("%d\n", liaison);
    if(liaison) segment_segmentBresenham(polygone->sommets->queue->point, p, BLANC);

    liste_ajouter(polygone->sommets, p);

    //polygone_dessiner(polygone);
}


void polygone_insererSommet(Polygone *polygone, Point p, Point suivant)
{
    int rang = 0;
    Maillon *sommet = polygone->sommets->tete;

    // insertion autorisée à partir de 2 sommets
    if(liste_taille(polygone->sommets) < 2) return;

    /* Calcul du rang de suivant dans le polygone */
    while(sommet && !point_sontEgaux(sommet->point, suivant))
    {
        sommet = sommet->suivant;
        rang++;
    }

    /* Traitement graphique léger mais sale */
//    change_point(p.x, p.y, JAUNE);
//    if(liste_estVide(polygone->sommets)) return;
//    if(sommet != polygone->sommets->tete)
//    {
//        segment_segmentBresenham(sommet->precedent->point, p, BLANC);
//        segment_segmentBresenham(sommet->precedent->point, sommet->point, NOIR);
//    }
//    segment_segmentBresenham(p, sommet->point, BLANC);

    /* Insertion dans le polygone */
    liste_inserer(polygone->sommets, p, rang);

    /* Traitement graphique lourd mais propre */
    polygone_dessiner(polygone, 1);
}


void polygone_supprimerSommet(Polygone *polygone, Point p)
{
    Maillon* m = polygone->sommets->tete;
    int rang = 0;

    /* Calcul du rang de p dans le polygone */
    while(m && !point_sontEgaux(m->point, p))
    {
        m = m->suivant;
        rang++;
    }

    /* Traitement graphique léger mais sale */
//    change_point(p.x, p.y, NOIR);
//    if(liste_estVide(polygone->sommets)) return;
//    if(m != polygone->sommets->tete)
//    {
//        segment_segmentBresenham(m->precedent->point, p, NOIR);
//    }
//    if(m != polygone->sommets->queue)
//    {
//        segment_segmentBresenham(p, m->suivant->point, NOIR);
//    }
//    if(m != polygone->sommets->tete && m != polygone->sommets->queue)
//    {
//        segment_segmentBresenham(m->precedent->point, m->suivant->point, BLANC);
//    }


    /* Suppression dans le polygone */
    liste_supprimerRang(polygone->sommets, rang);


    /* Traitement graphique lourd mais propre */
    polygone_dessiner(polygone, 1);
}


void polygone_deplacerSommet(Polygone *polygone, Point p, Point direction)
{
    Maillon* m = polygone_sommet(polygone, p);
    if(!m) return;

    m->point = direction;

    polygone_dessiner(polygone, 1);
}


Maillon* polygone_sommet(Polygone *polygone, Point p)
{
    Maillon* m = polygone->sommets->tete;

    /* Calcul du rang de p dans le polygone */
    while(m)
    {
        if(point_sontEgaux(m->point, p)) return m;
        m = m->suivant;
    }
    return NULL;
}

int polygone_rang(Polygone *polygone, Point p)
{
    Maillon* m = polygone->sommets->tete;
    int rang = 0;

    /* Calcul du rang de p dans le polygone */
    while(m)
    {
        if(point_sontEgaux(m->point, p)) return rang;
        m = m->suivant;
        rang++;
    }

    return -1;
}

void polygone_dessiner(Polygone* p, int clear)
{
    Maillon *sommet = p->sommets->tete;

    if(clear) efface_tout();

    while(sommet)
    {
        change_point(sommet->point.x,sommet->point.y,JAUNE);
        if(sommet->precedent) segment_segmentBresenham(sommet->precedent->point, sommet->point, BLANC);
        sommet = sommet->suivant;
    }
    if(p->ferme) segment_segmentBresenham(p->sommets->queue->point, p->sommets->tete->point, BLANC);
}


void polygone_selectionneSommetSuivant(Polygone* polygone)
{
    if (!polygone->pointCourant)    // S'il n'y a pas de point selectionne, on prend le premier
    {
        polygone->pointCourant = polygone->sommets->tete;
    }
    
    else
    {
        change_point(polygone->pointCourant->point.x, polygone->pointCourant->point.y, JAUNE); // Retablissement de la couleur du point courant
        
        if (polygone->pointCourant->suivant) {
            polygone->pointCourant = polygone->pointCourant->suivant;
        }
        else polygone->pointCourant = polygone->sommets->tete;
    }
    
    // Changement de la couleur du sommet selectionne
    change_point(polygone->pointCourant->point.x, polygone->pointCourant->point.y, BLEU);
}


void polygone_selectionneSommetPrecedent(Polygone* polygone)
{
    if (!polygone->pointCourant)    // S'il n'y a pas de point selectionne, on prend le dernier
    {
        polygone->pointCourant = polygone->sommets->queue;
    }
    
    else
    {
        change_point(polygone->pointCourant->point.x, polygone->pointCourant->point.y, JAUNE); // Retablissement de la couleur du point courant
        
        if (polygone->pointCourant->precedent) {
            polygone->pointCourant = polygone->pointCourant->precedent;
        }
        else polygone->pointCourant = polygone->sommets->queue;
    }
    
    // Changement de la couleur du sommet selectionne
    change_point(polygone->pointCourant->point.x, polygone->pointCourant->point.y, BLEU);
}


void polygone_deselectionne(Polygone* polygone)
{
    if (polygone && polygone->pointCourant) {
        change_point(polygone->pointCourant->point.x, polygone->pointCourant->point.y, JAUNE);
        polygone->pointCourant = NULL;
    }
}



Point polygone_sommetLePlusProche(Polygone *polygone, Point p)
{
    double distance, distance_min;
    Point proche;
    Maillon *sommet;

    if(!polygone || liste_estVide(polygone->sommets)) return point(0,0);

    distance_min = point_distance(p, polygone->sommets->tete->point);
    proche = polygone->sommets->tete->point;

    sommet = polygone->sommets->tete;
    while(sommet)
    {
        distance = point_distance(p, sommet->point);
        if(distance < distance_min)
        {
            distance_min = distance;
            proche = sommet->point;
        }
        sommet = sommet->suivant;
    }

    return proche;
}


Maillon* polygone_segmentLePlusProche(Polygone *polygone, Point p)
{
    double distance, distance_min, scalaire, distancePointProjete;
    Maillon *sommet, *res;
    Droite d;
    
    if(!polygone || liste_estVide(polygone->sommets)) return NULL;
    
    distance_min = point_distance(p, polygone->sommets->tete->point);
    res = polygone->sommets->tete;
    
    sommet = polygone->sommets->tete;
    while (sommet) {
        if (sommet->suivant) {
            scalaire = (sommet->suivant->point.x - sommet->point.x)*(p.x - sommet->point.x) + (sommet->suivant->point.y - sommet->point.y)*(p.y - sommet->point.y);
            distancePointProjete = scalaire / point_distance(sommet->point, sommet->suivant->point);
            
            // Si le projete orthogonal n'est pas sur le segment et se situe avant le premier point
            if (distancePointProjete < 0) {
                distance = point_distance(p, sommet->point);
            }
            
            // Si le projete orthogonal n'est pas sur le segment et se situe apres le deuxieme point
            else if (distancePointProjete > point_distance(sommet->point, sommet->suivant->point)) {
                distance = point_distance(p, sommet->suivant->point);
            }
            
            // Si le projete orthogonal est sur le segment
            else {
                d = droite_obtenirEquation(sommet->point, sommet->suivant->point);
                distance = droite_distancePointDroite(p, d);
            }
            
            if(distance < distance_min)
            {
                distance_min = distance;
                res = sommet;
            }
        }
        sommet = sommet->suivant;
    }
    
    return res;
}



void polygone_remplirGraine(Point pgraine)
{
    int xgraine = pgraine.x, ygraine = pgraine.y;
    Couleur c = val_point(xgraine, ygraine);
    
    if(c != NOIR) return;
    
    if( xgraine < 0 || xgraine > hauteur_ecran() || ygraine < 0 || ygraine > largeur_ecran() )
    {
        return;
    }
    
    change_point(xgraine,ygraine,ROUGE);
    polygone_remplirGraine(point(xgraine-1, ygraine));
    polygone_remplirGraine(point(xgraine, ygraine-1));
    polygone_remplirGraine(point(xgraine+1, ygraine));
    polygone_remplirGraine(point(xgraine, ygraine+1));
}


void polygone_remplirScanline(Polygone* p, Couleur couleur)
{
//    change_point(p->pmin.x, p->pmin.y, couleur);
//    change_point(p->pmax.x, p->pmax.y, couleur);

    int xmin = p->pmin.x, xmax = p->pmax.x, ymin = p->pmin.y, ymax = p->pmax.y;
    int x, y;
    int interieur;
    Point entree;

    if(!p->ferme) return;

    for (y = ymin; y < ymax; y++)
    {
        interieur = 0;
        for (x = xmin; x < xmax; x++)
        {
            if (val_point(x, y) != NOIR && val_point(x+1, y) == NOIR)
            {
                interieur = (interieur+1)%2;
                entree.x = x+1;
                entree.y = y;
            }
            else if (val_point(x, y) == NOIR && interieur)
            {
                change_point(x, y, couleur);
            }
        }
        if(interieur) // effacement d'erreur
        {
            segment_tracerSegmentHorizontal(entree, point(x, y), NOIR);
        }
    }
}




void polygone_remplirScanline2(Polygone* p, Couleur couleur)
{
//    change_point(p->pmin.x, p->pmin.y, couleur);
//    change_point(p->pmax.x, p->pmax.y, couleur);

    int xmin = p->pmin.x, xmax = p->pmax.x, ymin = p->pmin.y, ymax = p->pmax.y;
    int x, y;
    int interieur, deja_colorie;
    Point entree;

    if(!p->ferme) return;

    deja_colorie = 0;
    for (y = ymin; y < ymax; y++)
    {
        interieur = 0;
        for (x = xmin; x < xmax; x++)
        {
            if (val_point(x, y) == NOIR && interieur)
            {
                change_point(x, y, couleur);
                deja_colorie = 1;
            }
            else if (val_point(x, y) != NOIR && val_point(x+1, y) != NOIR)
            {
                interieur = 1;
                entree.x = x+1;
                entree.y = y;
            }
            else if (val_point(x, y) != NOIR && val_point(x+1, y) == NOIR && deja_colorie)
            {
                interieur = (interieur+1)%2;
                entree.x = x+1;
                entree.y = y;
            }
            else if (val_point(x, y) == NOIR && val_point(x+1, y) != NOIR)
            {
                interieur = 0;
            }
        }
        if(interieur) // effacement d'erreur
        {
            segment_tracerSegmentHorizontal(entree, point(x, y), NOIR);
        }
    }
}

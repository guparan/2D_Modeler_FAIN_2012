#include <stdio.h>
#include <stdlib.h>
#include "liste.h"


Liste *liste_creer()
{
    Liste *l = (Liste*) malloc(sizeof(Liste));
    l->tete = NULL;
    l->queue = NULL;
    return l;
}


void liste_detruireListe(Liste* l)
{
    liste_detruireListeMaillons(l->tete);
    free(l);
}


void liste_detruireListeMaillons(Maillon* m)
{
    if (!m) return;
    liste_detruireListeMaillons(m->suivant);
    printf("Destruction du maillon : %d, %d\n", m->point.x, m->point.y);
    free(m);
}

void liste_supprimer(Liste* l, Maillon* m)
{
    Maillon *sommet = l->tete;
    if(liste_estVide(l)) return;
    if(l->tete == l->queue) // un seul element dans la liste
    {
        l->tete = NULL;
        l->queue = NULL;
        free(sommet);
        return;
    }

    while(sommet)
    {
        if(sommet == m)
        {
            sommet->precedent->suivant = sommet->suivant;
            sommet->suivant->precedent = sommet->precedent;
            free(sommet);
            return;
        }
        sommet = sommet->suivant;
    }
}

void liste_supprimerRang(Liste* l, int rang)
{
    int n = 0;
    Maillon* sommet = l->tete;

    while(sommet)
    {
        if(n == rang)
        {
            if(sommet == l->tete)
            {
                l->tete = sommet->suivant;
            }
            else
            {
                sommet->precedent->suivant = sommet->suivant;
            }

            if(sommet == l->queue)
            {
                l->queue = sommet->precedent;
            }
            else
            {
                sommet->suivant->precedent = sommet->precedent;
            }
            free(sommet);
            return;
        }
        sommet = sommet->suivant;
        n++;
    }
}


booleen liste_estVide(Liste* l)
{
    return (!l->tete || !l->queue);
}


void liste_ajouter(Liste *l, Point p)
{
    puts("liste_ajouter");
    Maillon *m = (Maillon*) malloc (sizeof(Maillon));
    m->point = p;
    m->suivant = NULL;
    m->precedent = NULL;
    if(liste_estVide(l)) // m est le premier element de l
    {
        l->tete = m;
        l->queue = m;
    }
    else
    {
        m->precedent = l->queue;
        l->queue->suivant = m; // insertion de l'element
        l->queue = m; // mise à jour de la queue
    }
}


void liste_inserer(Liste *l, Point p, int rang)
{
    int n = 0;
    Maillon* nouveau;
    Maillon* sommet = l->tete;

    if(liste_estVide(l))
    {
        liste_ajouter(l, p);
    }

    while(sommet)
    {
        if(n == rang)
        {
            nouveau = (Maillon*) malloc(sizeof(Maillon));
            nouveau->point = p;
            nouveau->suivant = sommet;
            nouveau->precedent = sommet->precedent;

            if(sommet == l->tete) l->tete = nouveau;
            else sommet->precedent->suivant = nouveau;
            sommet->precedent = nouveau;

            return;
        }
        sommet = sommet->suivant;
        n++;
    }
}


booleen liste_appartient(Point p, Liste* l)
{
    Maillon *m = l->tete;
    while(m)
    {
        if (point_sontEgaux(p, m->point)) return vrai;
        m = m->suivant;
    }
    return faux;
}


int liste_taille(Liste* l)
{
    Maillon *m = l->tete;
    int res = 0;

    while(m)
    {
        res++;
        m = m->suivant;
    }
    return res;
}


Liste* liste_concat(Liste *l1, Liste *l2)
{
    l1->queue->suivant = l2->tete;
    return l1;
}


int liste_position(Point p, Liste* l)
{
    int pos = 0;
    Maillon *m = l->tete;
    while(m)
    {
        if (point_sontEgaux(p, m->point)) return pos;

        pos++;
        m = m->suivant;
    }
    return pos;
}




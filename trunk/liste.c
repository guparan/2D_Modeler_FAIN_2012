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
    printf("queue : %p\n", l->queue);
    free(l);
    //l=NULL;
}


void liste_detruireListeMaillons(Maillon* m)
{
    if (!m) return;
    liste_detruireListeMaillons(m->suivant);
    printf("Destruction du maillon : %d, %d\n", m->point.x, m->point.y);
    free(m);
    //m=NULL;
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
    if(liste_estVide(l)) return;

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


//void liste_ajout (Liste* l, Point p)
//{
//    Liste liste;
//    liste.point = p;
//    liste.suivant = &l;
//    return liste;
//}


void liste_ajouter(Liste *l, Point p)
{
//	Liste tmp = l;
	
//    if (tmp.suivant == NULL) {
//		tmp.suivant = malloc(sizeof(struct maillon));
//        tmp.suivant->point = e;
//	}
//	else {
//		tmp = *tmp.suivant;
//        liste_ajouter(tmp, e);
//	}
//	return l;
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


booleen liste_appartient(Point p, Liste* l)
{
//	int res = 0;
    
//    if (point_sontEgaux(p, l.point)) res = 1;
//	else if (l.suivant != NULL) res = liste_appartient(p, *l.suivant);
//    return res;

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
//    int res = 0;
    
//    while (l.suivant != NULL) {
//        l = *l.suivant;
//        res += 1;
//    }
//    return res;

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
//	Liste l = l1;

//    while (l.suivant != NULL) {
//        l = *l.suivant;
//    }
    
//    l.suivant = &l2;
//    return l1;

    l1->queue->suivant = l2->tete;
    return l1;
}


int liste_position(Point p, Liste* l)
{
//	int res = 1;
    
//    while (!point_sontEgaux(e, l.point)) {
//        if (l.suivant != NULL) {
//            res += 1;
//            l = *l.suivant;
//        }
//        else return 0;
//    }

//	return res;

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




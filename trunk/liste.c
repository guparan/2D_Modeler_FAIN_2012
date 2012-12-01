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

bool liste_estVide(Liste* l)
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


void liste_insere(Liste *l, Point p)
{
//	Liste tmp = l;
	
//    if (tmp.suivant == NULL) {
//		tmp.suivant = malloc(sizeof(struct maillon));
//        tmp.suivant->point = e;
//	}
//	else {
//		tmp = *tmp.suivant;
//        liste_insere(tmp, e);
//	}
//	return l;
    Maillon *m = (Maillon*) malloc (sizeof(Maillon));
    m->point = p;
    m->suivant = NULL;
    if(liste_estVide(l)) // m est le premier element de l
    {
        l->tete = m;
        l->queue = m;
    }
    else l->queue->suivant = m;
}


bool liste_appartient(Point p, Liste* l)
{
//	int res = 0;
    
//    if (point_egaux(p, l.point)) res = 1;
//	else if (l.suivant != NULL) res = liste_appartient(p, *l.suivant);
//    return res;

    Maillon *m = l->tete;
    while(m)
    {
        if (point_egaux(p, m->point)) return true;
        m = m->suivant;
    }
    return false;
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
    
//    while (!point_egaux(e, l.point)) {
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
        if (point_egaux(p, m->point)) return pos;

        pos++;
        m = m->suivant;
    }
    return pos;
}




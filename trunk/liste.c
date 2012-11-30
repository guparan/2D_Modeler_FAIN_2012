#include <stdio.h>
#include <stdlib.h>
#include "liste.h"


Liste liste_ajout (Liste l, Point nvelt)
{
	Liste p;
	p = malloc(sizeof(struct maillon));
	p->point = nvelt;
	p->suivant = l;
	return(p);
}


Liste liste_insere(Liste l, Point e)
{
	Liste res = l;
	if (l == NULL) {
		res = liste_ajout(NULL, e);
	}
	else {
		l->suivant = liste_insere(l->suivant, e);
	}
	return(res);
}


int liste_appartient(Point x, Liste l)
{
	if (l == NULL) return(0);
	if (point_egaux(x, l->point)) return(1);
	return(liste_appartient(x, l->suivant));
}


void liste_concat(Liste *l1, Liste l2)
{
	Liste l = *l1;
	if (l == NULL) *l1 = l2;
	else {
		while (l->suivant != NULL) {
			l = l->suivant;
		}
		l->suivant = l2;
	}
}


int liste_position(Point e, Liste l)
{
	int res = 0;
	if (l != NULL)
    {
		if (point_egaux(e, l->point)) res = 1;
		else res = 1 + liste_position(e,l->suivant);
	}
	return(res);
}


int liste_incluse(Liste l1, Liste l2)
{
	int res=1;
	if (l1 != NULL)
    {
		if (liste_position(l1->point, l2) == 0) res=0;
		else res = liste_incluse(l1->suivant, l2);
	}
	return(res);
}




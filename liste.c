#include <stdio.h>
#include <stdlib.h>
#include "liste.h"


Liste liste_creer (Point p)
{
    Liste l;
	l.point = p;
	return l;
}


Liste liste_ajout (Liste l, Point p)
{
	Liste liste;
	liste.point = p;
	liste.suivant = &l;
	return liste;
}


Liste liste_insere(Liste l, Point e)
{
	Liste tmp = l;
	
    if (tmp.suivant == NULL) {
		tmp.suivant = malloc(sizeof(struct maillon));
        tmp.suivant->point = e;
	}
	else {
		tmp = *tmp.suivant;
        liste_insere(tmp, e);
	}
	return l;
}


int liste_appartient(Point p, Liste l)
{
	int res = 0;
    
    if (point_egaux(p, l.point)) res = 1;
	else if (l.suivant != NULL) res = liste_appartient(p, *l.suivant);
    return res;
}


int liste_taille(Liste l)
{
    int res = 0;
    
    while (l.suivant != NULL) {
        l = *l.suivant;
        res += 1;
    }
    return res;
}


Liste liste_concat(Liste l1, Liste l2)
{
	Liste l = l1;

    while (l.suivant != NULL) {
        l = *l.suivant;
    }
    
    l.suivant = &l2;
    return l1;
}


int liste_position(Point e, Liste l)
{
	int res = 1;
    
    while (!point_egaux(e, l.point)) {
        if (l.suivant != NULL) {
            res += 1;
            l = *l.suivant;
        }
        else return 0;
    }

	return res;
}




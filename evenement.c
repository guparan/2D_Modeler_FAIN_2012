
#include <stdio.h>
#include "primitives.h"
#include "polygone.h"
#include "segment.h"
#include "evenement.h"
#include "point.h"


static Polygone* polygone = NULL;

static ModeEdition mode_edition;

Point point_insertion = {-1,-1};


void evenement_souris(int b,int s,int x,int y)
{
    int TAILLE_PIXEL = 7;
    int x2=x/TAILLE_PIXEL;
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    int y2=(height-1-y)/TAILLE_PIXEL;


    switch(b)
    {
        case GLUT_LEFT_BUTTON:
        {
            evenement_boutonGauche(x2, y2, s!=GLUT_DOWN); // etrange
            break;
        }
        case GLUT_MIDDLE_BUTTON:
        {
            evenement_boutonMilieu(x2, y2, s==GLUT_UP);
            break;
        }
        case GLUT_RIGHT_BUTTON:
        {
            evenement_boutonDroit(x2,y2,s==GLUT_UP);
            break;
        }
    }
  /*glutPostRedisplay();*/
    glutReportErrors();
}


void evenement_boutonDroit(int x, int y, int fin_click)
{
    static int x0,y0;

    printf("clic droit ");

    if(!fin_click) // quand clic enfonce : on retient le départ
    {
        puts("enfonce");
        x0=x;
        y0=y;
    }
    else // quand clic relaché
    {
        puts("relache");

        if(x0 == x && y0 == y) // si clic statique
        {

        }

        else // si clic glissé
        {
            change_point(x0, y0, VERT);
            segment_segmentBresenham(point(x0,y0), point(x,y), VERT);
            change_point(x, y, VERT);

            if(mode_edition == VERTEX) // si clic statique
            {
                if(polygone && !liste_estVide(polygone->sommets))
                {
                    polygone_deplacerSommet(polygone, point(x0, y0), point(x, y));
                }
            }
        }
    }
}


void evenement_boutonGauche(int x, int y, int fin_click)
{
    static int x0,y0;

    printf("clic gauche ");

    if(!fin_click) // quand clic enfonce : on retient le départ
    {
        puts("enfonce");
        x0=x;
        y0=y;
    }

    else
    {
        puts("relache");
        Point p;

        switch(mode_edition)
        {
            case INSERT :
                if(!point_sontEgaux(point_insertion, point(-1,-1))) // clic sur point suivant
                {
                    polygone_insererSommet(polygone, point_insertion, point(x, y));
                    point_insertion.x = -1;
                    point_insertion.y = -1;
                }
                else // clic sur point à insérer
                {
                    point_insertion.x = x;
                    point_insertion.y = y;
                }
                break;

            case EDGE :
                if (polygone->pointCourant && polygone->pointCourant->suivant) {
                    segment_segmentBresenham(polygone->pointCourant->point, polygone->pointCourant->suivant->point, BLANC);
                }
                polygone->pointCourant = polygone_segmentLePlusProche(polygone, point(x, y));
                if (polygone->pointCourant && polygone->pointCourant->suivant) {
                    segment_segmentBresenham(polygone->pointCourant->point, polygone->pointCourant->suivant->point, BLEU);
                }
                break;

            case VERTEX :
                if(polygone && polygone->pointCourant) // re-init du point courant
                {
                    change_point(polygone->pointCourant->point.x, polygone->pointCourant->point.y, JAUNE);
                }
                p = polygone_sommetLePlusProche(polygone, point(x,y));
                change_point(p.x, p.y, VERT);
                break;

            case APPEND :
                if(x0 == x && y0 == y) // si clic statique
                {
                    if(!polygone) // rien en mémoire
                    {
                        polygone = polygone_creer();
                        polygone_ajouterSommet(polygone, point(x, y), 0);
                    }
                    else // pour tout autre clic
                    {
                        polygone_ajouterSommet(polygone, point(x, y), 1);
                    }
                }
                break;
        }
    }
}


void evenement_boutonMilieu(int x, int y, int fin_click)
{
    if(fin_click) polygone_remplirGraine(point(x, y));
}


void evenement_clavier(unsigned char touche, int x, int y)
{
    printf("touche %c appuyee\n", touche);
    
    if (touche == 'f') {
        polygone_remplirScanline(polygone, ROUGE);
    }

    else if(touche == 'c' && polygone && liste_taille(polygone->sommets)>2) // tracé du polygone avec au moins 3 sommets
    {
        if(!polygone->ferme)
        {
            segment_segmentBresenham(polygone->sommets->queue->point, polygone->sommets->tete->point, BLANC);
            polygone->ferme = 1;
        }
        else
        {
            segment_segmentBresenham(polygone->sommets->queue->point, polygone->sommets->tete->point, NOIR);
            polygone->ferme = 0;
        }
    }
    
    else if (touche == 'n') {
        efface_tout();
        polygone_detruire(polygone);
        polygone = NULL; // indispensable
    }
    
    else if (touche == 'a') {
        mode_edition = APPEND;
        polygone_deselectionneSommet(polygone);
        polygone_deselectionneArete(polygone);
        puts("Prodramme en mode APPEND");
    }
    
    else if (touche == 'v') {
        mode_edition = VERTEX;
        polygone_deselectionneArete(polygone);
        puts("Prodramme en mode VERTEX");
    }
    
    else if (touche == 'e') {
        mode_edition = EDGE;
        polygone_deselectionneSommet(polygone);
        puts("Programme en mode EDGE");
    }

    else if (touche == 'i') // switch insertion mode
    {
        mode_edition = INSERT;
        polygone_deselectionneSommet(polygone);
        polygone_deselectionneArete(polygone);
        puts("Programme en mode INSERT");
    }
    
    else if (touche == 'p' && mode_edition == VERTEX) {
        polygone_selectionneSommetSuivant(polygone);
    }
    
    else if (touche == 'o' && mode_edition == VERTEX) {
        polygone_selectionneSommetPrecedent(polygone);
    }

    else if (touche == 127 && mode_edition == VERTEX && polygone && polygone->pointCourant) {
        polygone_supprimerSommet(polygone, polygone->pointCourant->point);
    }
}


void evenement_clavierSpecial(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_PAGE_UP :
            if (mode_edition == VERTEX) {
                polygone_selectionneSommetSuivant(polygone);
            }
            else if (mode_edition == EDGE)
            {
                polygone_selectionneAreteSuivante(polygone);
            }
            break;

        case GLUT_KEY_PAGE_DOWN :
            if (mode_edition == VERTEX) {
                polygone_selectionneSommetPrecedent(polygone);
            }
            else if (mode_edition == EDGE)
            {
                polygone_selectionneAretePrecedente(polygone);
            }
            break;

        case GLUT_KEY_UP :
            if (mode_edition == VERTEX && polygone && polygone->pointCourant) {
                polygone_deplacerSommet(polygone, polygone->pointCourant->point, point(polygone->pointCourant->point.x, polygone->pointCourant->point.y+1));
            }
            break;

        case GLUT_KEY_DOWN :
            if (mode_edition == VERTEX && polygone && polygone->pointCourant) {
                polygone_deplacerSommet(polygone, polygone->pointCourant->point, point(polygone->pointCourant->point.x, polygone->pointCourant->point.y-1));
            }
            break;

        case GLUT_KEY_LEFT :
            if (mode_edition == VERTEX && polygone && polygone->pointCourant) {
                polygone_deplacerSommet(polygone, polygone->pointCourant->point, point(polygone->pointCourant->point.x-1, polygone->pointCourant->point.y));
            }
            break;

        case GLUT_KEY_RIGHT :
            if (mode_edition == VERTEX && polygone && polygone->pointCourant) {
                polygone_deplacerSommet(polygone, polygone->pointCourant->point, point(polygone->pointCourant->point.x+1, polygone->pointCourant->point.y));
            }
            break;
    }
}

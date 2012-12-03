
#include <stdio.h>
#include "primitives.h"
#include "polygone.h"
#include "segment.h"
#include "evenement.h"
#include "point.h"


static Polygone* polygone = NULL;

static int mode_touche_c = BLANC;
static ModeEdition mode_edition;

int mode_suppr = 0;


void evenement_souris(int b,int s,int x,int y)
{
    int TAILLE_PIXEL = 10;
    int x2=x/TAILLE_PIXEL;
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    int y2=(height-1-y)/TAILLE_PIXEL;


    switch(b)
    {
        case GLUT_LEFT_BUTTON:
        {
            evenement_boutonGauche(x2, y2, s==GLUT_DOWN);
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
            if(mode_suppr)
            {
                polygone_supprimerSommet(polygone, point(x, y));
                polygone_dessiner(polygone, 1);
                return;
            }

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
        else // si clic glissé
        {
            segment_segmentBresenham(point(x0,y0), point(x,y), VERT);
        }
    }
}


void evenement_boutonGauche(int x, int y, int fin_click)
{
    if(fin_click) {
        change_point(x,y,!val_point(x,y));
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

    if(touche == 'c' && polygone && liste_taille(polygone->sommets)>2) // tracé du polygone avec au moins 3 sommets
    {
        if(mode_touche_c == BLANC)
        {
            segment_segmentBresenham(polygone->sommets->queue->point, polygone->sommets->tete->point, BLANC);
            polygone->ferme = 1;
            mode_touche_c = NOIR;
        }
        else
        {
            segment_segmentBresenham(polygone->sommets->queue->point, polygone->sommets->tete->point, NOIR);
            polygone->ferme = 0;
            mode_touche_c = BLANC;
        }
    }
    
    if (touche == 'e') {
        efface_tout();
        polygone_detruire(polygone);
        polygone = NULL; // indispensable
    }

    if(touche == 's')
    {
        mode_suppr = (mode_suppr+1)%2;
    }
    
    if (touche == 'a') {
        mode_edition = APPEND;
        puts("Prodramme en mode APPEND");
    }
    
    if (touche == 'v') {
        mode_edition = VERTEX;
        //polygone_selectionneSommetSuivant();
        puts("Prodramme en mode VERTEX");
    }
    
    if (touche == 'e') {
        mode_edition = EDGE;
        puts("Programme en mode EDGE");
    }
}

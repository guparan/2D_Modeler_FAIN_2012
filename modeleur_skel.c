#include <stdio.h>
#include "modeleurlib.h"

void remplir(int xgraine, int ygraine)
{
    couleur c = val_point(xgraine, ygraine);
    
    if(c == BLANC || c == ROUGE ) return;
    
    if( xgraine < 0 || xgraine > hauteur_ecran() || ygraine < 0 || ygraine > largeur_ecran() )
    {
        return;
    }

    change_point(xgraine,ygraine,ROUGE);
    remplir(xgraine-1, ygraine);
    remplir(xgraine, ygraine-1);
    remplir(xgraine+1, ygraine);
    remplir(xgraine, ygraine+1);
}


void tracer_segment(int xA,int yA,int xB,int yB, int octant)
{
    printf("Segment dans l'octant %d rapporté au 1er : (%d,%d) ; (%d,%d)\n", octant, xA, yA, xB, yB);
    int dx = xB - xA;
    int dy = yB - yA;
    int incr1 = 2*dy;
    int incr2 = 2*(dy-dx);
    int x = xA, y = yA;
    int d = 2*dy-dx;

    while(x < xB+1)
    {
//        printf("Boucle tracer_segment (xB==%d) : x==%d\n", xB, x);
        switch (octant)
        {
            case 1 : change_point(x, y, BLANC); break;
            case 2 : change_point(y, x, BLANC); break;
            case 3 : change_point(y, -x, BLANC); break;
            case 4 : change_point(-x, y, BLANC); break;
            case 5 : change_point(-x, -y, BLANC); break;
            case 6 : change_point(-y, -x, BLANC); break;
            case 7 : change_point(-y, x, BLANC); break;
            case 8 : change_point(x, -y, BLANC); break;
        }
        
        x++;
        if(d < 0)
        {
            d = d + incr1;
        }
        else
        {
            y++;
            d = d + incr2;
        }
    }
}


void tracer_segment_vertical(int xA, int yA, int yB) {
    int y;

    if (yA<yB) {
        for (y = yA; y < yB+1; y++) {
            change_point(xA, y, BLANC);
        }
    }
    else {
        for (y = yA; y > yB-1; y--) {
            change_point(xA, y, BLANC);
        }
    }
}


void tracer_segment_horizontal(int yA, int xA, int xB) {
    int x;

    if (xA<xB) {
        for (x = xA; x < xB+1; x++) {
            change_point(x, yA, BLANC);
        }
    }
    else {
        for (x = xA; x > xB-1; x--) {
            change_point(x, yA, BLANC);
        }
    }
}


void segment(int xA,int yA,int xB,int yB)
{
    int dx = xB - xA;
    int dy = yB - yA;
    
    printf("Points cliqués pour le segment : (%d, %d), (%d,%d)\n", xA, yA, xB, yB);

    if (dx == 0)
    {
        tracer_segment_vertical(xA, yA, yB);
    }
    else if (dy == 0)
    {
        tracer_segment_horizontal(yA, xA, xB);
    }
    else if(dx > 0 && dy > 0 && dx > dy) // 1er octant
    {
        tracer_segment(xA, yA, xB, yB, 1);
    }
    else if(dx > 0 && dy > 0 && dx < dy) // 2eme octant
    {
        tracer_segment(yA, xA, yB, xB, 2);
    }
    else if(dx < 0 && dy > 0 && abs(dx) < dy) /* 3eme octant /!\ */
    {
        tracer_segment(-yB, xB, -yA, xA, 3);
    }
    else if(dx < 0 && dy > 0 && abs(dx) > dy) // 4eme octant
    {
        tracer_segment(-xA, yA, -xB, yB, 4);
    }
    else if(dx < 0 && dy < 0 && abs(dx) > abs(dy)) // 5eme octant
    {
        tracer_segment(-xA, -yA, -xB, -yB, 5);
    }
    else if(dx < 0 && dy < 0 && abs(dx) < abs(dy)) // 6eme octant
    {
        tracer_segment(-yA, -xA, -yB, -xB, 6);
    }
    else if(dx > 0 && dy < 0 && dx < abs(dy)) /* 7eme octant /!\ */
    {
        tracer_segment(yB, -xB, yA, -xA, 7);
    }
    else if(dx > 0 && dy < 0 && dx > abs(dy)) // 8eme octant
    {
        tracer_segment(xA, -yA, xB, -yB, 8);
    }
}


void action_bouton_droit(int x, int y, int fin_click)
{
  if(fin_click) remplir(x,y);
}


void action_bouton_milieu(int x, int y, int fin_click)
{
  static int x0,y0;
  if(fin_click) printf("fin"); else printf("debut");
  printf(" appui bouton du milieu de la souris\n");
  if(fin_click) {
    segment(x0,y0,x,y);
  }
  else {
    x0=x; y0=y;
  }
}


void action_clavier(unsigned char touche, int x, int y)
{
  printf("touche %c appuyee\n", touche);
}

int main(int nargs, char **args)
{
  main_Modeleurlib(nargs,args);
  return 0;
}

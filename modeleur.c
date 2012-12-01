#include "modeleur.h"
#include "primitives.h"
#include "segment.h"


void modeleur_ligneBrisee()
{
    Point points[10];
    int i;

    for(i=0 ; i<10 ; i++)
    {
        points[i].x = i*5+(i%2)*4;
        points[i].y = i*2+(i%2)*9;
    }

    segment_testSegment(points, 10);
}


int main(int nargs, char **args)
{
    initPrimitives(nargs,args);


    /* Questions du projet */

    // modeleur_ligneBrisee();


    /* Fin questions */


    glutMainLoop(); // Lancement de l'application
    return 0;
}

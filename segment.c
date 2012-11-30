#include <stdio.h>
#include "primitives.h"
#include "segment.h"


void segment_tracerSegment(int xA,int yA,int xB,int yB, int octant, couleur couleur)
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
//        printf("Boucle segment_tracerSegment (xB==%d) : x==%d\n", xB, x);
        switch (octant)
        {
            case 1 : change_point(x, y, couleur); break;
            case 2 : change_point(y, x, couleur); break;
            case 3 : change_point(-y, x, couleur); break;
            case 4 : change_point(-x, y, couleur); break;
            case 5 : change_point(-x, -y, couleur); break;
            case 6 : change_point(-y, -x, couleur); break;
            case 7 : change_point(y, -x, couleur); break;
            case 8 : change_point(x, -y, couleur); break;
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


void segment_tracerSegmentVertical(int xA, int yA, int yB, couleur couleur) {
    int y;

    if (yA<yB) {
        for (y = yA; y < yB+1; y++) {
            change_point(xA, y, couleur);
        }
    }
    else {
        for (y = yA; y > yB-1; y--) {
            change_point(xA, y, couleur);
        }
    }
}


void segment_tracerSegmentHorizontal(int yA, int xA, int xB, couleur couleur) {
    int x;

    if (xA<xB) {
        for (x = xA; x < xB+1; x++) {
            change_point(x, yA, couleur);
        }
    }
    else {
        for (x = xA; x > xB-1; x--) {
            change_point(x, yA, couleur);
        }
    }
}


void segment_segmentBresenham(int xA,int yA,int xB,int yB, couleur couleur)
{
    int dx = xB - xA;
    int dy = yB - yA;
    
    printf("Points cliqués pour le segment : (%d, %d), (%d,%d)\n", xA, yA, xB, yB);

    if (dx == 0)
    {
        segment_tracerSegmentVertical(xA, yA, yB, couleur);
    }
    else if (dy == 0)
    {
        segment_tracerSegmentHorizontal(yA, xA, xB, couleur);
    }
    else if(dx > 0 && dy > 0 && dx > dy) // 1er octant
    {
        segment_tracerSegment(xA, yA, xB, yB, 1, couleur);
    }
    else if(dx > 0 && dy > 0 && dx < dy) // 2eme octant
    {
        segment_tracerSegment(yA, xA, yB, xB, 2, couleur);
    }
    else if(dx < 0 && dy > 0 && abs(dx) < dy) /* 3eme octant /!\ */
    {
        segment_tracerSegment( yA, -xA,yB, -xB, 3, couleur);
    }
    else if(dx < 0 && dy > 0 && abs(dx) > dy) // 4eme octant
    {
        segment_tracerSegment(-xA, yA, -xB, yB, 4, couleur);
    }
    else if(dx < 0 && dy < 0 && abs(dx) > abs(dy)) // 5eme octant
    {
        segment_tracerSegment(-xA, -yA, -xB, -yB, 5, couleur);
    }
    else if(dx < 0 && dy < 0 && abs(dx) < abs(dy)) // 6eme octant
    {
        segment_tracerSegment(-yA, -xA, -yB, -xB, 6, couleur);
    }
    else if(dx > 0 && dy < 0 && dx < abs(dy)) /* 7eme octant /!\ */
    {
        segment_tracerSegment( -yA, xA, -yB, xB, 7, couleur);
    }
    else if(dx > 0 && dy < 0 && dx > abs(dy)) // 8eme octant
    {
        segment_tracerSegment(xA, -yA, xB, -yB, 8, couleur);
    }
}

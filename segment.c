#include <stdio.h>
#include "primitives.h"
#include "segment.h"



void segment_testSegment()
{
    Point A = point(10,20);
    Point B = point(40, 50);

    segment_segmentBresenham(A, B, BLANC);
}

void segment_tracerSegment(Point A, Point B, int octant, Couleur couleur)
{
    printf("Segment dans l'octant %d rapporté au 1er : (%d,%d) ; (%d,%d)\n", octant, A.x, A.y, B.x, B.y);
    int dx = B.x - A.x;
    int dy = B.y - A.y;
    int incr1 = 2*dy;
    int incr2 = 2*(dy-dx);
    int x = A.x, y = A.y;
    int d = 2*dy-dx;

    while(x < B.x+1)
    {
//        printf("Boucle segment_tracerSegment (B.x==%d) : x==%d\n", B.x, x);
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

void segment_tracerSegmentVertical(Point A, Point B, Couleur couleur) {
    int y;

    if (A.y<B.y) {
        for (y = A.y; y < B.y+1; y++) {
            change_point(A.x, y, couleur);
        }
    }
    else {
        for (y = A.y; y > B.y-1; y--) {
            change_point(A.x, y, couleur);
        }
    }
}


void segment_tracerSegmentHorizontal(Point A, Point B, Couleur couleur) {
    int x;

    if (A.x<B.x) {
        for (x = A.x; x < B.x+1; x++) {
            change_point(x, A.y, couleur);
        }
    }
    else {
        for (x = A.x; x > B.x-1; x--) {
            change_point(x, A.y, couleur);
        }
    }
}


void segment_segmentBresenham(Point A, Point B, Couleur couleur)
{
    int dx = B.x - A.x;
    int dy = B.y - A.y;
    
    printf("Points cliqués pour le segment : (%d, %d), (%d,%d)\n", A.x, A.y, B.x, B.y);

    if (dx == 0)
    {
        segment_tracerSegmentVertical(point(A.x, A.y), point(0, B.y), couleur);
    }
    else if (dy == 0)
    {
        segment_tracerSegmentHorizontal(point(A.y, A.x), point(B.x, 0), couleur);
    }
    else if(dx > 0 && dy > 0 && dx > dy) // 1er octant
    {
        segment_tracerSegment(point(A.x, A.y), point(B.x, B.y), 1, couleur);
    }
    else if(dx > 0 && dy > 0 && dx < dy) // 2eme octant
    {
        segment_tracerSegment(point(A.y, A.x), point(B.y, B.x), 2, couleur);
    }
    else if(dx < 0 && dy > 0 && abs(dx) < dy) /* 3eme octant /!\ */
    {
        segment_tracerSegment( point(A.y, -A.x),point(B.y, -B.x), 3, couleur);
    }
    else if(dx < 0 && dy > 0 && abs(dx) > dy) // 4eme octant
    {
        segment_tracerSegment(point(-A.x, A.y), point(-B.x, B.y), 4, couleur);
    }
    else if(dx < 0 && dy < 0 && abs(dx) > abs(dy)) // 5eme octant
    {
        segment_tracerSegment(point(-A.x, -A.y), point(-B.x, -B.y), 5, couleur);
    }
    else if(dx < 0 && dy < 0 && abs(dx) < abs(dy)) // 6eme octant
    {
        segment_tracerSegment(point(-A.y, -A.x), point(-B.y, -B.x), 6, couleur);
    }
    else if(dx > 0 && dy < 0 && dx < abs(dy)) /* 7eme octant /!\ */
    {
        segment_tracerSegment( point(-A.y, A.x), point(-B.y, B.x), 7, couleur);
    }
    else if(dx > 0 && dy < 0 && dx > abs(dy)) // 8eme octant
    {
        segment_tracerSegment(point(A.x, -A.y), point(B.x, -B.y), 8, couleur);
    }
}

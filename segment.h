
#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

/* Détermine dans quel octant le segment se trouve et demande le tracé à la fonction tracer_segment */
void segment_segmentBresenham(Point A, Point B, Couleur couleur);

/* Trace un segment dans un octant donné */
void segment_tracerSegment(Point A, Point B, int octant, Couleur couleur);
void segment_tracerSegmentVertical(Point A, Point B, Couleur couleur);
void segment_tracerSegmentHorizontal(Point A, Point B, Couleur couleur);

#endif

#ifndef FAIN_TP1_segment_h
#define FAIN_TP1_segment_h

/* Détermine dans quel octant le segment se trouve et demande le tracé à la fonction tracer_segment */
void segment_segmentBresenham(int xA,int yA,int xB,int yB, couleur couleur);

/* Trace un segment dans un octant donné */
void segment_tracerSegment(int xA,int yA,int xB,int yB, int octant, couleur couleur);
void segment_tracerSegmentVertical(int xA, int yA, int yB, couleur couleur);
void segment_tracerSegmentHorizontal(int yA, int xA, int xB, couleur couleur);

#endif

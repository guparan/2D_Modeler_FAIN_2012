//
//  segment.h
//  FAIN-TP1
//
//  Created by Lucas Saurel on 29/11/12.
//  Copyright (c) 2012 Lucas Saurel. All rights reserved.
//

#ifndef FAIN_TP1_segment_h
#define FAIN_TP1_segment_h

/* Détermine dans quel octant le segment se trouve et demande le tracé à la fonction tracer_segment */
void segment_segmentBresenham(int xA,int yA,int xB,int yB);
/* Trace un segment dans un octant donné */
void segment_tracerSegment(int xA,int yA,int xB,int yB, int octant);
void segment_tracerSegmentVertical(int xA, int yA, int yB);
void segment_tracerSegmentHorizontal(int yA, int xA, int xB);

#endif

#ifndef _VMATH_H
#define _VMATH_H

#include <math.h>

#include "main.h"

/* from perlin.c */
float noise2(float vec[2]);

float noise( float, float );
float power( float, int );
void rotate( float*, float*, float, float, float );
vertex_t perspective_divide( vertex_t );
float orient( vertex_t, vertex_t, vertex_t );
vertex_t vnormal( vertex_t, vertex_t, vertex_t );
float vdotproduct( vertex_t, vertex_t );
vertex_t vsub( vertex_t, vertex_t );
vertex_t vnormalize( vertex_t );

#endif

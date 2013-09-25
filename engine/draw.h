#ifndef _DRAW_H
#define _DRAW_H

#ifdef __WIN32
	#include <windows.h>
	#include <gl/gl.h>
	#include <gl/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glx.h>
	#include <GL/glu.h>
#endif

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "struct.h"

/* we_draw_vertex_init: init vertex mass for draw_ñircle */
void we_draw_vertex_init(int seg);

/* we_vertex_free: free allocation memory */
void we_draw_vertex_free(void);

/* we_draw_circle3f: drawing circle */
void we_draw_circle3f(float x, float y, float r);

/* we_draw_alpha_circle3f: drawing alpha circle */
void we_draw_alpha_circle3f(float x, float y, float r);

/* we_set_color: return color struct */
we_color we_draw_color3f(float r, float g, float b);
we_color we_draw_color4f(float r, float g, float b, float a);

extern void *we_malloc(size_t size);
extern void we_free(void *ptr);

#endif

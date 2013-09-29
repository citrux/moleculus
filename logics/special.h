#ifndef __SPECIAL_H__
#define __SPECIAL_H__

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

typedef struct {
	float r;
	float g;
	float b;
	float a;
} sp_color;

float spGetFps( void );
void spDrawString( float x, float y, const char *fmt, ... );
void spVertexInit( int segment );
void spDrawCircle3f( float x, float y, float r );
void spFree( void );
sp_color spColor3f( float r, float g, float b );
sp_color spColor4f( float r, float g, float b, float a );

#endif
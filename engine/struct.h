#ifndef _STRUCT_H
#define _STRUCT_H

#include <GL/gl.h>

typedef struct {
	float aspect;
	float angle;
	float zNear;
	float zFar;
} we_option;
/* perspective option */

typedef struct {
	char *name;
	char *appclass;
	int width;
	int height;
	int fullscreen;
	int debug;
	int argc;
	char **argv;
	we_option proj;
	int max_fps;
} we_engine;
/* engine struct */

typedef struct {
	float r, g, b, a;
} we_color;
/* color struct */

typedef struct {
	int size;
	int weight;
	char *name;
	GLuint base;
} we_font;
/* font struct */

#ifdef __WIN32
    typedef unsigned __int64 uint;
#endif

#define WE_FAILED 						 -1
#define WE_SUCCESS 						 1

#define WE_MEDIUM                        0
#define WE_BOLD                          1
/* font param */

#define WE_LBUTTON_DOWN                  0
#define WE_RBUTTON_DOWN                  1
#define WE_MBUTTON_DOWN                  2
#define WE_LBUTTON_UP                    3
#define WE_RBUTTON_UP                    4
#define WE_MBUTTON_UP                    5

#endif

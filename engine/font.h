#ifndef _FONT_H
#define _FONT_H

#ifdef __WIN32
	#include <windows.h>
	#include <gl/gl.h>
	#include <gl/glu.h>
#else
	#include <GL/gl.h>
	#include <GL/glx.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "struct.h"
#include "error.h"

/* we_font_build: init font */
void we_font_build(we_font * font);

/* we_printf: output text */
void we_font_printf(we_font *f, float x, float y, const char *fmt, ...);

/* we_font_kill: free using font */
void we_font_kill(void);

extern void *we_malloc(size_t size);
extern void we_free(void *ptr);

#endif

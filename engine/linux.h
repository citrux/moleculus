#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/extensions/xf86vmode.h>
#include <X11/keysym.h>
#include "struct.h"
#include "error.h"
#include "keyboard.h"

typedef struct {
    Display *dsp;
    int screen;
    Window wnd;
    Window root;
    GLXContext ctx;
    XSetWindowAttributes swa;
    Bool doubleBuffered;
    XF86VidModeModeInfo deskMode;
    XVisualInfo *vi;
    XWindowAttributes gwa;
    int fullscreen;
    int x, y, depth;
} GLWindow;

/* we_window_create: create engine window */
int we_window_create(we_engine * engine);

/* we_loop: main event system */
void we_loop(we_engine * engine);

/* we_kill: destroy window */
void we_kill(void);

/* we_render: rendering callback function */
void we_render(void (*param)(void));

/* we_init: opengl init function */
void we_init(void (*param)(void));

/* we_keyboard: keyboard callback function */
void we_keyboard(void (*param)(int*));

/* we_mouse: mouse callback function */
void we_mouse(void (*param)(int, float, float));

/* we_mouse_pos: get mouse position */
void we_mouse_pos(float *x, float *y);

/* we_quit: close program */
void we_quit(void);

/* we_opengl_swapbuffers: swap buffer */
void we_opengl_swapbuffers();

/* we_window_mode: change window mode */
void we_window_mode(we_engine * engine);

/* we_window_update: update window param's */
void we_window_update(we_engine *engine);

/* we_update_caption: update window caption */
void we_window_caption(const char *fmt, ...);

extern void we_resize(int width, int height, we_option *option);
extern void we_info();
extern void *we_malloc(size_t size);
extern void we_free(void *ptr);
extern void we_param(we_engine * engine);
extern uint we_ticks(void);
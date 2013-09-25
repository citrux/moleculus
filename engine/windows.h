#include <windows.h>
#include <windowsx.h>
#include <stdint.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "struct.h"
#include "error.h"
#include "keyboard.h"

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

/* we_window_mode: change window mode */
void we_window_mode(we_engine * engine);

/* we_opengl_swapbuffers: swap buffer */
void we_opengl_swapbuffers();

/* we_window_update: update window param's */
void we_window_update(we_engine *engine);

/* we_window_caption: update window caption */
void we_window_caption(const char *fmt, ...);

extern void we_info();
extern void we_resize(int width, int height, we_option *option);
extern void we_param(we_engine *engine);
extern uint we_ticks();

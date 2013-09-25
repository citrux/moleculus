#ifndef _ERROR_H
#define _ERROR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// прописать ошибки

enum {
	ERROR_NONE,
// linux
	ERROR_OPEN_DISPLAY,
	ERROR_GLX_VERSION,
	ERROR_GLX_SUPPORT,
	ERROR_CHOOSE_VISUAL,
	ERROR_DRAW_CONTEXT,
// windows
	ERROR_REGISTER_WINDOW,
	ERROR_CREATE_WINDOW,
	ERROR_CREATE_CONTEXT,
	ERROR_GETDC_CONTEXT,
	ERROR_CHOOSE_PIXELFORMAT,
	ERROR_SET_PIXELFORMAT,
	ERROR_MAKE_CONTEXT,
	ERROR_CLEAR_CONTEXT,
	ERROR_DELETE_CONTEXT,
	ERROR_FULLSCR_MODE,
// other
	ERROR_LOAD_FONT,
	ERROR_ALLOC_MEMORY
};

enum {
	INFO_DOUBLE_BUFFER,
	INFO_SINGLE_BUFFER
};

/* we_error_print: print engine error */
void we_error_print(void);

/* we_error_send: send error from system */
void we_error_send(int error);

/* we_error_get: get engine error */
int we_error_get(void);

/* we_info_print: print engine information */
void we_info_print(void);

/* we_info_send: send info from system */
void we_info_send(int info);

/* we_info_get: get engine information */
int we_info_get(void);

#endif

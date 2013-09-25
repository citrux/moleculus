#ifdef __WIN32
	#include "windows.h"
#else
	#include <sys/utsname.h>
	#include <sys/sysinfo.h>
	#include <sys/time.h>
	#include <unistd.h>
	#include <execinfo.h>
	#include <GL/glu.h>
	#include "linux.h"
#endif

#include <malloc.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>

/* we_info: get system info */
void we_info(void);

/* we_about: get engine info */
void we_about(char **name, char **version);

/* we_getfps: calculate fps */
float we_getfps(void);

// not using
/* we_tics: get cpu tic's */
// uint we_rdtsc(void);

/* we_ticks: get system tic's from platform */
uint we_ticks(void);

/* we_malloc: allocate memory */
void *we_malloc(size_t size);

/* we_realloc: reallocate memory */
void *we_realloc(void *a, size_t size);

/* we_free: free allocating memory */
void we_free(void *ptr);

/* we_resize: resize window */
void we_resize(int width, int height, we_option *option);

/* we_param: working with console param's */
void we_param(we_engine *engine);

/* we_memory_usage: return allocating memory in bytes */
size_t we_memory_usage();

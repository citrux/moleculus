#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include "struct.h"
#include "vector.h"
#include "image.h"

typedef struct {
    vec3 pos;
    vec3 vel;
    vec3 acc;
    vec3 p0;
    vec3 v0;
    vec3 a0;
	int life;
	we_color color;
} particle;

typedef struct {
    particle *a;
    float *data;
    float *color;
    float fade;
    float particle_size;
    int particle_count;
    int particle_draw;
    int max_life;
    int alpha_flag;
    int spawn_count;
    char *particle_image;
    texture_image tex;
    float *texture;
} particle_sys;

/* we_particle_init: initializing particle_sys struct */
void we_particle_init(particle_sys *p);

/* we_particle_set: set specific param to particle_sys */
void we_particle_set(particle_sys *p);

/* we_particle_draw: draw particle_sys */
void we_particle_draw(particle_sys *p);

/* we_particle_spawn: using spawn method for generate particle */
void we_particle_spawn(particle_sys *p);

/* we_particle_move: move particle */
void we_particle_move(particle_sys *p, float dt);

/* we_particle_destroy: deinitializing particle_sys struct */
void we_particle_destroy(particle_sys *p);

extern void *we_malloc(size_t size);
extern void we_free(void *ptr);

#endif

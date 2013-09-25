#ifndef _MODEL_H
#define _MODEL_H

#include <stdio.h>
#include "struct.h"

#ifdef __linux__
    #include <sys/stat.h>
    long filelength(int handle);
#endif

typedef struct {
	float u, v;
} mapcoord_type;

typedef struct {
	float x, y, z;
} vertex_type;

typedef struct {
	int a, b, c;
	mapcoord_type map_a, map_b, map_c;
} polygon_type;

typedef struct {
	vertex_type *vertex;
	polygon_type *polygon;
	mapcoord_type *mapcoord;
	int id_texture;
	unsigned short vertices_qty;
	unsigned short polygons_qty;
	unsigned short texture_qty;
	int textured;
	char m_name[32];
} obj_3ds;

typedef struct {
    float *vertex;
    float *texture;
    int vertex_n;
    int texture_n;
} vertex_p;

/* we_model_load_3ds: loading 3ds model */
int we_model_load_3ds(obj_3ds *b, char *filename);

/* we_model_generate: converting model to opengl compatible format */
void we_model_generate(vertex_p *a, obj_3ds *b);

extern void *we_malloc(size_t size);
extern void we_free(void *ptr);

#endif

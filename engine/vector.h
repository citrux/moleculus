#ifndef _VEC_H
#define _VEC_H

#include <math.h>

typedef struct {
	float x, y;
} vec2;

typedef struct {
    float x, y, z;
} vec3;

vec2 v2_set(float x, float y);
vec2 v2_add(vec2 a, vec2 b);
vec2 v2_sub(vec2 a, vec2 b);
vec2 v2_mul(vec2 a, float k);
vec2 v2_div(vec2 a, float k);
vec2 v2_norm(vec2 a);
vec2 v2_abs(vec2 a);
float v2_dot(vec2 a, vec2 b);
float v2_length(vec2 a);

vec3 v3_set(float x, float y, float z);
vec3 v3_add(vec3 a, vec3 b);
vec3 v3_sub(vec3 a, vec3 b);
vec3 v3_mul(vec3 a, float k);
vec3 v3_div(vec3 a, float k);
vec3 v3_norm(vec3 a);
vec3 v3_abs(vec3 a);
vec3 v3_cross(vec3 a, vec3 b);
float v3_dot(vec3 a, vec3 b);
float v3_length(vec3 a);

#endif

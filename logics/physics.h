#ifndef __PHYS_H__
#define __PHYS_H__

#include "vector.h"
#include "point.h"

void elastic_collision( point *p_i, point *p_j );
void inelastic_collision( point *p_i, point *p_j );
void adhesion( point *p_i, point *p_j );

Vector2 newton_force( point *p_i, point *p_j );
Vector2 coulomb_force( point *p_i, point *p_j );

#endif

#ifndef _PHYS_H
#define _PHYS_H

#include "vector.h"
#include "special.h"

typedef struct {
    Vector2 pos;                    // позиция
    Vector2 vel;                    // скорость
    Vector2 acc, acc_1, acc_2;      // ускорение [3x]
    we_color c;                     // цвет
    float radius;                   // радиус
    float mass;                     // масса
    float q;                        // заряд
} point;


typedef struct {
    point fst, snd;
} two_points;


two_points elastic_collision(point p_i, point p_j);
two_points inelastic_collision(point p_i, point p_j);
two_points adhesion(point p_i, point p_j);

Vector2 newton_force(point p_i, point p_j);
Vector2 coulomb_force(point p_i, point p_j);

#endif

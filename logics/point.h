#ifndef __POINT_H__
#define __POINT_H__

#include "special.h"

typedef struct {
    Vector2 pos;                    // позиция
    Vector2 vel;                    // скорость
    Vector2 acc, acc_1, acc_2;      // ускорение [3x]
    sp_color c;                     // цвет
    float radius;                   // радиус
    float mass;                     // масса
    float q;                        // заряд
} point;

#endif
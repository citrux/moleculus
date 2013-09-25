#ifndef _MAIN_H
#define _MAIN_H

#include "vector.h"
#include "physics.h"
#include "configure.h"
extern "C" {
	#include "../engine/memory.h"
}

/* phys_init: функция инициализации физического движка */
void phys_init(float xborder, float yborder, float px, float py);
/* phys_free: функция очистки используемых ресурсов */
void phys_free();

/* phys_do: функция обработки физики */
void phys_do();
/* phys_move: функция передвижения шариков */
void phys_move(float dt);
/* phys_collide: функция обработки столкновений */
void phys_collide(int i, int j);
/* phys_count: функция получения количества шариков */
int phys_count();
/* phys_energy: функция получения энергии системы */
float phys_energy();

/* phys_point: функция получения информации о точке */
point * phys_point();
/* phys_border: установка границ симуляции */
void phys_border(float bx, float by);

/* acceleration: функция установки типа ускорения */
Vector2 acceleration(int i);

#endif

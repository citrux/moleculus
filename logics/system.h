#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "vector.h"
#include "special.h"
#include "point.h"
#include "physics.h"

/* коэффициент расположения частиц */
const float kf = 3.0f;

class System {
public:
	~System();
	void Init( void );
	void Load( const char *file );
	void Do( void );
	void Move( float dt );
	void Collide( int i, int j );
	Vector2 Acceleration( int i );
	void Draw( void );
	int getCount( void );
	float getEnergy( void );
	void setCount( int count );
	void setBorder( float x_border, float y_border );
private:
	float xborder = 55.0f, yborder = 55.0f;
	int ext_interaction = 2;
	int check_energy = 1;
	int interaction = 0;
    int gravity_dim = 3;
    int start_speed = 10;
	int max_count = 100;
	int hit_type = 0;
    int borders = 1;
    float radius = 2.0f;
    float G = 10.0f, E = 10.0f;
    point * p = NULL;
};

#endif
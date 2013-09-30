#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include "vector.h"
#include "special.h"
#include "point.h"
#include "physics.h"

/* коэффициент расположения частиц */
const float kf = 3.0f;

class System {
public:
	~System();
	void SystemInit( void );
	void SystemLoad( const char *file );
	void SystemDo( void );
	void SystemMove( float dt );
	void SystemCollide( int i, int j );
	Vector2 SystemAcceleration( int i );
	void SystemDraw( void );
	int getSystemCount( void );
	float getSystemEnergy( void );
	void setSystemCount( int count );
	void setSystemBorder( float x_border, float y_border );
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
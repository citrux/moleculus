#include "system.h"

static const char default_config[] =  
    "# количество шариков\nMAX_COUNT = %d\n\n"
    "# радиус шариков\nRADIUS = %.2f\n\n"
    "# вывод энергии [0/1]\nCHECK_ENERGY = %d\n\n"
    "# границы [0/1]\nBORDERS = %d\n\n# тип внешнего взаимодействия:\n"
    "# 0 - нет\n# 1 - центральное\n# 2 - гравитационное поле\n"
    "EXT_INTERACTION = %d\n\n# тип взаимодействия:\n"
    "# 0 - нет\n# 1 - гравитация [между шариками]\n"
    "# 2 - электромагнитное взаимодействие [пока только Кулон]\n"
    "# 3 - 1 + 2\nINTERACTION = %d\n\n"
    "# размерность пространства для Ньютоновской механики GRAVITY_DIM = 3\n"
    "GRAVITY_DIM = %d\n\n# гравитационная постоянная\nG = %.2f\n\n"
    "# электрическая постоянная\nE = %.2f\n\n# тип соудорения:\n"
    "# 0 - упруго\n# 1 - неупруго\n# 2 - слипание [жидкость]\n"
    "HIT_TYPE = %d\n\n# скорость при стартовом разлёте\nSTART_SPEED = %d";

System::~System()
{
	delete [] p;
}

void System::SystemInit( void )
{
	float px = -xborder, py = -yborder;

	p = new point [max_count];
	for ( int i = 0; i < max_count; i++ ) {
		p[i].pos = Vector2( px, py );
		if ( start_speed > 0 ) {
			p[i].vel = Vector2( rand()%start_speed - start_speed / 2.0f, 
				rand()%start_speed - start_speed / 2.0f );
		} else {
			p[i].vel = Vector2( 0.0f, 0.0f );
		}
		p[i].acc = Vector2( 0.0f, 0.0f );
		p[i].acc_1 = Vector2( 0.0f, 0.0f );
		p[i].acc_2 = Vector2( 0.0f, 0.0f );
		p[i].radius = radius;
		p[i].q = ( i%2 - 0.5f );
		p[i].mass = 1;
		p[i].c = spColor3f( 0.0f, 0.5f, 1.0f );
		if ( px < xborder - 2.0f ) {
			px += radius * kf;
		} else {
			py += radius * kf;
			px = -xborder;
		}
	}
}

void System::SystemLoad( const char *file )
{
	/* add a code */
}

void System::SystemDo( void )
{
	for ( int i = 0; i < max_count; i++ ) {
		if ( borders ) {
            int near_w, move_to_wall;
			/* удар о плоскость стенки, параллельной yOz */
			near_w = ( fabs( p[i].pos.x ) + p[i].radius ) > xborder;
			move_to_wall = ( p[i].vel.x * p[i].pos.x ) > 0.0f;
			if ( near_w && move_to_wall ) {
				p[i].vel.x = -p[i].vel.x;
			}
			/* удар о плоскость стенки, параллельной xOz */
			near_w = ( fabs( p[i].pos.y ) + p[i].radius ) > yborder;
			move_to_wall = ( p[i].vel.y * p[i].pos.y ) > 0.0f;
			if ( near_w && move_to_wall ) {
				p[i].vel.y = -p[i].vel.y;
			}
		}
		for ( int j = i + 1; j < max_count; j++ ) {
			SystemCollide( i, j );
		}
	}
}

void System::SystemMove( float dt )
{
	for ( int i = 0; i < max_count; i++ ) {
		p[i].pos += p[i].vel * dt + p[i].acc * dt*dt/2.0f;
        p[i].vel = p[i].vel + p[i].acc * dt;
		p[i].acc = SystemAcceleration( i );
	}
}

void System::SystemCollide( int i, int j )
{
	float rad = p[i].radius + p[j].radius;
	Vector2 vi = p[i].vel, vj = p[j].vel;
	Vector2 delta = p[i].pos - p[j].pos;
	Vector2 n = delta.norm(); // для соударения -- вектор направления центров

	int before_contact = (vj - vi) * n > 0;
    int mass_exists = p[i].mass * p[j].mass > 0;      // наличие массы
	if ( ( delta.length() < rad ) && before_contact && mass_exists )
	{
		switch ( hit_type ) {
			case 0:
				elastic_collision( &p[i], &p[j] );
				break;
			case 1:
				inelastic_collision( &p[i], &p[j] );
				break;
			case 2:
				adhesion( &p[i], &p[j] );
				break;
		}
	}
}

Vector2 System::SystemAcceleration( int i )
{
	Vector2 gravity, elect, r, acc;

	switch ( ext_interaction ) {
		case 0:
            acc = Vector2( 0.0f, 0.0f );
			break;
		case 1:
			acc = Vector2( -p[i].pos.x, -p[i].pos.y );
			break;
		case 2:
			acc = Vector2( 0.0f, -10.0f );
			break;
		default:
			std::cout << "error: ext_interaction out of range [0,2]" << std::endl;
			break;
	}
	switch ( interaction ) {
		case 0:
			break;
		case 1:
			gravity = Vector2( 0.0f, 0.0f );
			for (int j = 0; j < max_count; j++) {
				int not_into = ( p[j].pos - p[i].pos ).length() >
					p[i].radius + p[j].radius;
				if ( not_into && j != i ) {
					gravity += newton_force( &p[i], &p[j] );
				}
			}
			acc += gravity * G;
			break;
		case 2:
			elect = Vector2( 0.0f, 0.0f );
			for ( int j = 0; j < max_count; j++ ) {
				int not_into = ( p[j].pos - p[i].pos ).length() >
					p[i].radius + p[j].radius;
				if ( not_into && j != i ) {
					elect += coulomb_force( &p[i], &p[j] );
				}
			}
			acc += elect * E;
			break;
		case 3:
			elect = Vector2( 0.0f, 0.0f );
			gravity = Vector2( 0.0f, 0.0f );
			for ( int j = 0; j < max_count; j++ ) {
				int not_into = ( p[j].pos - p[i].pos ).length() >
					p[i].radius + p[j].radius;
				if ( not_into ) {
					elect += coulomb_force( &p[i], &p[j] );
					gravity += newton_force( &p[i], &p[j] );
				}
				acc += elect * E + gravity * G;
			}
			break;
		default:
			std::cout << "error: interaction out of range [0,3]" << std::endl;
			break;
	}
	return acc;
}

void System::SystemDraw( void )
{
	for ( int i = 0; i < max_count; i++ ) {
		glColor3f( p[i].c.r, p[i].c.g, p[i].c.b );
        spDrawCircle3f( p[i].pos.x, p[i].pos.y, p[i].radius );
	}
}

int System::getSystemCount( void )
{
	return max_count;
}

float System::getSystemEnergy( void )
{
	float ENERGY;
	for ( int i = 0; i < max_count; i++ ) {
		if ( ext_interaction == 2 ) {
			ENERGY += p[i].mass * 10.0f * p[i].pos.y;
		} else {
			ENERGY += p[i].mass * ( p[i].vel * p[i].vel ) / 2.0f;
		}
	}
	return ENERGY / max_count;
}

void System::setSystemCount( int count )
{
	max_count = count;
}

void System::setSystemBorder( float x_border, float y_border )
{
	xborder = x_border;
	yborder = y_border;
}

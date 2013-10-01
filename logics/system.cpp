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

void System::Init( void )
{
	float px = -xborder, py = -yborder;

	if ( p != NULL ) {
		delete [] p;
	}
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

void System::Load( const char *file )
{
	using std::cout;
	using std::endl;
	using std::ifstream;
	using std::ofstream;
	const int MAX_LINE = 256;
	const int MAX_TOKEN = 4;
	const char * const DELIMETER = " = ";
	ifstream fr;
	ofstream fw;

	fr.open( file );
	if ( fr.good() ) {
		while ( !fr.eof() ) {
			char buf[MAX_LINE];
			fr.getline( buf, MAX_LINE );
			if ( buf[0] == '#' ) {
				continue;
			}
			int n = 0;
			const char * token[MAX_TOKEN] = {};
			token[0] = strtok( buf, DELIMETER );
			if ( !token[0] ) {
				continue;
			} else  {
				for ( n = 1; n < MAX_TOKEN; n++ ) {
					token[n] = strtok( 0, DELIMETER );
					if ( !token[n] ) {
						break;
					}
				}
				if ( !strcmp( "MAX_COUNT", token[0] ) ) {
					max_count = atoi( token[1] );
				} else if ( !strcmp( "RADIUS", token[0] ) ) {
					radius = (float) atof( token[1] );
				} else if ( !strcmp( "CHECK_ENERGY", token[0] ) ) {
					check_energy = atoi( token[1] );
				} else if ( !strcmp( "BORDERS", token[0] ) ) {
					borders = atoi( token[1] );
				} else if ( !strcmp( "INTERACTION", token[0] ) ) {
					interaction = atoi( token[1] );
				} else if ( !strcmp( "GRAVITY_DIM", token[0] ) ) {
					gravity_dim = atoi( token[1] );
				} else if ( !strcmp( "G", token[0] ) ) {
					G = (float) atof( token[1] );
				} else if ( !strcmp( "E", token[0] ) ) {
					E = (float) atof( token[1] );
				} else if ( !strcmp( "HIT_TYPE", token[0] ) ) {
					hit_type = atoi( token[1] );
				} else if ( !strcmp( "START_SPEED", token[0] ) ) {
					start_speed = atoi( token[1] );
				}
			}
		}
		fr.close();
	} else {
		fw.open( file );
		if ( !fw.good() ) {
			cout << "[Error]: Can't create " << file << "!" << endl;
		}
		fw << "# количество шариков\n" << "MAX_COUNT = " << max_count << "\n\n";
		fw << "# радиус шариков" << endl << "RADIUS = " << radius << "\n\n";
		fw << "# вывод энергии [0/1]" << endl << "CHECK_ENERGY = " << check_energy << "\n\n";
		fw << "# границы [0/1]" << endl << "BORDERS = " << borders << "\n\n";
		fw << "# тип внешнего взаимодействия:\n# 0 - нет\n# 1 - центральное\n";
		fw << "# 2 - гравитационное поле\n" << "EXT_INTERACTION = " << ext_interaction << "\n\n";
		fw << "# тип взаимодействия:\n# 0 - нет\n# 1 - гравитация [между шариками]\n";
		fw << "# 2 - электромагнитное взаимодействие [пока только Кулон]\n# 3 - 1 + 2\n";
		fw << "INTERACTION = " << interaction << "\n\n";
		fw << "# размерность пространства для Ньютоновской механики GRAVITY_DIM = 3\n";
		fw << "GRAVITY_DIM = " << gravity_dim << "\n\n";
		fw << "# гравитационная постоянная\nG = " << G << "\n\n";
		fw << "# электрическая постоянная\nE = " << E << "\n\n";
		fw << "# тип соудорения:\n# 0 - упруго\n# 1 - неупруго\n# 2 - слипание [жидкость]\n";
		fw << "HIT_TYPE = " << hit_type << "\n\n";
		fw << "# скорость при стартовом разлёте\n" << "START_SPEED = " << start_speed;
		fw.close();
	}
}

void System::Do( void )
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
			Collide( i, j );
		}
	}
}

void System::Move( float dt )
{
	for ( int i = 0; i < max_count; i++ ) {
		p[i].pos += p[i].vel * dt + p[i].acc * dt*dt/2.0f;
        p[i].vel = p[i].vel + p[i].acc * dt;
		p[i].acc = Acceleration( i );
	}
}

void System::Collide( int i, int j )
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

Vector2 System::Acceleration( int i )
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

void System::Draw( void )
{
	for ( int i = 0; i < max_count; i++ ) {
		glColor3f( p[i].c.r, p[i].c.g, p[i].c.b );
        spDrawCircle3f( p[i].pos.x, p[i].pos.y, p[i].radius );
	}
}

int System::getCount( void )
{
	return max_count;
}

float System::getEnergy( void )
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

void System::setCount( int count )
{
	max_count = count;
}

void System::setBorder( float x_border, float y_border )
{
	xborder = x_border;
	yborder = y_border;
}

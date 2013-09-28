#include <stdarg.h>
#include <GL/glut.h>
#include "logics/main.h"

int win_id = 0;

static int MAX_COUNT;
float aspect;
float border;
float fps;
float px = -20.0f;
float py = -10.0f;
float dt = 1.0f / 60.0f;
int p_pause = 0;

const int EMAX = 300;
int e_count = 0;
float energy[EMAX+1];
float buffer[2*EMAX];

point *a;

static char *text;
int segment = 36;
float *vertex;
float *ver;

void draw_string( float x, float y, const char *fmt, ... )
{
	va_list ap;

	va_start( ap, fmt );
    vsprintf( text, fmt, ap );
    va_end( ap );

	glRasterPos2f( x, y );
	while ( *text ) {
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *text++ );
	}
}

void we_draw_vertex_init(int seg)
{
    int j = 0;
    float i;

    segment = seg;

    vertex = new float [2*seg];
    ver = new float [2*seg];

    /* инициализируем массив для единичного круга */
    for (i = 0; i <= 360.0f; i += (360.0f / segment)) {
        vertex[j++] = cos(i*M_PI/180.0f);
        vertex[j++] = sin(i*M_PI/180.0f);
    }
}

void we_draw_circle3f(float x, float y, float r)
{
    /* подумать о надобности этой функции */
    GLfloat color[4];
    int i;

    for (i = 0; i < 2*segment+2; i += 2) {
        ver[i] = vertex[i] * r + x;
        ver[i+1] = vertex[i+1] * r + y;
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    /* рисуем первую окружность */
    glVertexPointer(2, GL_FLOAT, 0, ver);
    glDrawArrays(GL_POLYGON, 0, segment+1);

    glDisableClientState(GL_VERTEX_ARRAY);
}

void init()
{
    static int count = 0;
	
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	text = new char [64];

    aspect = 58.0f;

    we_draw_vertex_init(32);

    if (count < 1) {
	    phys_init(border, border, px, py);
        MAX_COUNT = phys_count();
    	a = phys_point();
    }
    count++;
}

void keyboard( unsigned char key, int x, int y )
{
    if ( key == 'q' ) {
        glutDestroyWindow( win_id );
    }
    else if ( key == ' ' ) {
        p_pause = !p_pause;
    }
    else if ( key == 'r' ) {
        phys_init(border, border, px, py);
        MAX_COUNT = phys_count();
        a = phys_point();
    }
}

void draw_graph()
{
    float max;

    max = energy[0];
    for (int i = 1; i < e_count; i++)
        if (max < energy[i])
            max = energy[i];

    for (int i = 0; i < e_count; i += 2) {
        buffer[i+0] = aspect / 2.0f + (i/2) * 0.2f;
        buffer[i+1] = aspect / 1.5f + 16.0f * energy[i] / max;
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, buffer);
    glDrawArrays(GL_LINE_STRIP, 0, e_count / 2);
    glDisableClientState(GL_VERTEX_ARRAY);

    if (!p_pause) {
        if (e_count < EMAX)
            e_count++;
        else
            for (int i = 0; i < e_count; i++)
                energy[i] = energy[i+1];

        energy[e_count] = phys_energy();
    }
}

void render( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 0.0f);
    
    glLineWidth(1.1f);
    for (int i = 0; i < MAX_COUNT; i++) {
        glColor3f(a[i].c.r, a[i].c.g, a[i].c.b);
        we_draw_circle3f( a[i].pos.x, a[i].pos.y, a[i].radius );
    }
    
    draw_graph();
    
    glColor3f( 1.0f, 1.0f, 1.0f );
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string( -aspect, aspect - 0.03f*aspect, "N: %d", MAX_COUNT );
	draw_string( -aspect, aspect - 0.09f*aspect, "E: %.4f", phys_energy() );
    
    if (p_pause) {
        draw_string( -aspect, aspect - 0.15f*aspect, "paused" );
    }
        
    phys_do();
    
    if (!p_pause)
        phys_move(dt);
    
    glutSwapBuffers();
}

void redraw( int value )
{
	render();
	glutTimerFunc( 30, redraw, 0 );
}

void resize(int width, int height )
{
    GLfloat param1 = (float) width / height;
    GLfloat n = 60.0f;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width <= height)
        glOrtho(-n, n, -n/param1, n/param1, n, -n);
    else
        glOrtho(-n * param1, n * param1, -n, n, n, -n);

    gluPerspective( 0.0f, param1, 1.0f, 100.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{	
    glutInit( &argc, argv );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    win_id = glutCreateWindow( "Moleculus" );
    glutReshapeFunc( resize );
    glutDisplayFunc( render );
    glutKeyboardFunc( keyboard );
    glutTimerFunc( 30, redraw, 0 );
    init();
    glutMainLoop();
    phys_free();
    delete [] text;
    delete [] ver;
    delete [] vertex;
	return 0;
}

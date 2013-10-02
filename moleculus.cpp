#include <GL/glut.h>
#include "logics/special.h"
#include "logics/system.h"

int win_id = 0;
System sys;

void program_init( void )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    spVertexInit( 32 );
    sys.Load( "config.txt" );
    sys.Init();
}

void program_render( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
    sys.Do();
    sys.Move( 1.0 / 30.0f );
    sys.Draw();
    glColor3f( 1.0f, 1.0f, 1.0f );
    spDrawString( -55.0f, 55.0f - 0.03f*55.0f, "N: %d", sys.getCount() );
    spDrawString( -55.0f, 55.0f - 0.09f*55.0f, "E: %.4f", sys.getEnergy() );
    spDrawString( -55.0f, 55.0f - 0.15f*55.0f, "FPS: %.1f", spGetFps() );
	glutSwapBuffers();
}

void program_redraw( int value )
{
	program_render();
	glutTimerFunc( 30, program_redraw, 0 );
}

void program_resize( int width, int height )
{
	GLfloat param1 = (float) width / height;
    GLfloat n = 60.0f;

    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if ( width <= height ) {
        glOrtho( -n, n, -n/param1, n/param1, n, -n );
    } else {
        glOrtho( -n * param1, n * param1, -n, n, n, -n );
    }
    gluPerspective( 0.0f, param1, 1.0f, 100.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void program_keyboard( unsigned char key, int x, int y )
{
    static int fullscreen = 1;
    if ( key == 'q' ) {
        glutDestroyWindow( win_id );
    } else if ( key == 'f' ) {
        if ( fullscreen ) {
            glutFullScreen();
        } else {
            glutReshapeWindow( 500, 500 );
        }
        fullscreen = !fullscreen;
    } else if ( key == 'r' ) {
        sys.Load( "config.txt" );
        sys.Init();
    }
}

void program_free( void )
{
	spFree();
}

int main( int argc, char *argv[] )
{
	glutInit( &argc, argv );
    glutInitWindowSize( 500, 500 );
    glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    win_id = glutCreateWindow( "Moleculus" );
    glutReshapeFunc( program_resize );
    glutDisplayFunc( program_render );
    glutKeyboardFunc( program_keyboard );
    glutTimerFunc( 30, program_redraw, 0 );
    program_init();
    glutMainLoop();
    program_free();
    return EXIT_SUCCESS;
}

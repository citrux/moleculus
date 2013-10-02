#include <GL/glut.h>
#include "logics/special.h"
#include "logics/system.h"

int w_width = 500;
int w_height = 500;
int win_id = 0;
System sys;
GLfloat n = 60.0f;
GLfloat aspect;

void program_init( void )
{
    GLint sw = glutGet( GLUT_SCREEN_WIDTH );
    GLint sh = glutGet( GLUT_SCREEN_HEIGHT );
    glutPositionWindow( ( sw - w_width ) / 2, ( sh - w_height) / 2 );
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glEnable( GL_LINE_SMOOTH );
    glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    spVertexInit( 24 );
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
    spDrawString( -n + 1.0f, n - 3.0f, "N: %d", sys.getCount() );
    spDrawString( -n + 1.0f, n - 6.0f, "E: %.4f", sys.getEnergy() );
    spDrawString( -n + 1.0f, n - 9.0f, "FPS: %.1f", spGetFps() );
    glutSwapBuffers();
}

void program_redraw( int value )
{
    program_render();
    glutTimerFunc( 30, program_redraw, 0 );
}

void program_resize( int width, int height )
{
    aspect = (float) width / height;
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if ( width <= height ) {
        glOrtho( -n, n, -n/aspect, n/aspect, n, -n );
    } else {
        glOrtho( -n * aspect, n * aspect, -n, n, n, -n );
    }
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
            glutReshapeWindow( w_width, w_height );
        }
        fullscreen = !fullscreen;
    } else if ( key == 'r' ) {
        sys.Load( "config.txt" );
        sys.Init();
    } else if ( key == 'b' ) {
        sys.checkBorderDraw();
    }
}

void program_free( void )
{
    spFree();
}

int main( int argc, char *argv[] )
{
    glutInit( &argc, argv );
    glutInitWindowSize( w_width, w_height );
    glutInitWindowPosition( 0, 0 );
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

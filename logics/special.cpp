#include "special.h"

static float * vertex = NULL;
static int segment_g = 16;

float spGetFps( void )
{
	static int FrameCount = 0;
	static float NewCount = 0.0f, LastCount = 0.0f, FpsRate = 0.0f;

    NewCount = (float) glutGet( GLUT_ELAPSED_TIME );
    if ( ( NewCount - LastCount ) > 1000 ) {
        FpsRate = ( FrameCount * 1000 ) / ( NewCount - LastCount );
        LastCount = NewCount;
        FrameCount = 0;
    }
    FrameCount++;
    return FpsRate;
}

void spDrawString( float x, float y, const char *fmt, ... )
{
	char buffer[256];
	char * text = buffer;
	va_list ap;

	va_start( ap, fmt );
    vsprintf( text, fmt, ap );
    va_end( ap );
	glRasterPos2f( x, y );
	while ( *text ) {
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *text++ );
	}
}

void spVertexInit( int segment )
{
    int j = 0;

    segment_g = segment;
    vertex = new float [2*(segment+2)];
    for ( float i = 0; i <= 360.0f; i += ( 360.0f / segment ) ) {
        vertex[j++] = cos( i * M_PI / 180.0f);
        vertex[j++] = sin( i * M_PI / 180.0f);
    }
    vertex[j++] = cos( 0.0f );
    vertex[j++] = sin( 0.0f );
}

void spDrawCircle3f( float x, float y, float r )
{
	glLineWidth( r );
    glPushMatrix();
    glTranslatef( x, y, 0 );
    glScalef( r, r, 0 );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 2, GL_FLOAT, 0, vertex );
    glDrawArrays( GL_POLYGON, 0, segment_g + 1 );
    glColor3f( 1.0f, 1.0f, 1.0f );
    glDrawArrays( GL_LINE_STRIP, 0, segment_g + 1 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glPopMatrix();
}

void spFree( void )
{
	delete [] vertex;
}

sp_color spColor3f( float r, float g, float b )
{
	return { r, g, b, 1.0f };
}

sp_color spColor4f( float r, float g, float b, float a )
{
	return { r, g, b, a };
}
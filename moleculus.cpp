#include "logics/main.h"
extern "C" {
    #include "engine/kernel.h"
    #include "engine/unit/font.h"
};

uiFont font;

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

int segment = 36;
float *vertex;
float *ver;

void we_draw_vertex_init(int seg)
{
    int j = 0;
    float i;

    segment = seg;

    vertex = (float *) weCalloc( 2*seg, sizeof(float) );
    ver = (float *) weCalloc( 2*seg, sizeof(float) );

    /* инициализируем массив для единичного круга */
    for (i = 0; i <= 360.0f; i += (360.0f / segment)) {
        vertex[j++] = cos(i*M_PI/180.0f);
        vertex[j++] = sin(i*M_PI/180.0f);
    }
}

void we_draw_alpha_circle3f(float x, float y, float r)
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

    /* а теперь вторую (только контур) с прозрачностью */
    glGetFloatv(GL_CURRENT_COLOR, color);
    glColor4f(color[0], color[1], color[2], 0.5f);
    glDrawArrays(GL_LINE_LOOP, 0, segment+1);
    glColor4f(color[0], color[1], color[2], color[3]);

    glDisableClientState(GL_VERTEX_ARRAY);
}
void init()
{
    static int count = 0;
    
    uiFontRasterBuild( &font, 10, 0, "Terminus" );
    // border = engine.proj.aspect - 2.0f;
	
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
	glEnable(GL_BLEND);

    aspect = 58.0f;

    /*
	font.size = 14;
	font.weight = WE_MEDIUM;
	font.name = "terminus";
    we_font_build(&font);
	
    aspect = engine.proj.aspect;
	aspect -= 0.05f*aspect;

    */
    we_draw_vertex_init(32);

    if (count < 1) {
	    phys_init(border, border, px, py);
        MAX_COUNT = phys_count();
    	a = phys_point();
    }
    count++;
}

void keyboard( unsigned int *map )
{
    if ( map['q'] || map[WE_KEY_ESCAPE] ) {
        weKill();
    }
    if ( map[' '] ) {
        p_pause = !p_pause;
    }
    if ( map['r'] ) {
        phys_init(border, border, px, py);
        MAX_COUNT = phys_count();
        a = phys_point();
    }
    /*
    if (keycode[WE_Q] || keycode[WE_ESC])
        we_quit();
    if (keycode[WE_F1] || keycode[WE_F]) {
        we_window_mode(&engine);
		we_window_update(&engine);
    }
    if (keycode[WE_SPACE])
        p_pause = !p_pause;
    if (keycode[WE_R]) {
        phys_init(border, border, px, py);
        MAX_COUNT = phys_count();
        a = phys_point();
    }
    */
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

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, 0.0f);
	
	fps = weGetFps();
    
    glLineWidth(1.1f);
    for (int i = 0; i < MAX_COUNT; i++) {
        glColor3f(a[i].c.r, a[i].c.g, a[i].c.b);
        we_draw_alpha_circle3f(a[i].pos.x, a[i].pos.y, a[i].radius);
    }
        
    glDisable(GL_BLEND);
    
    draw_graph();
    
	glColor3f(1.0f, 1.0f, 1.0f);
	uiFontPrintf(&font, -aspect, aspect - 0.03f*aspect, "N: %d", MAX_COUNT);
	uiFontPrintf(&font, -aspect, aspect - 0.09f*aspect, "E: %.4f", phys_energy());
    uiFontPrintf(&font, -aspect, -aspect, "FPS: %.1f", fps);
    
    if (p_pause)
        uiFontPrintf(&font, -aspect, aspect - 0.15f*aspect, "paused");
        
    glEnable(GL_BLEND);
        
    phys_do();
    
    if (!p_pause)
        phys_move(dt);
    
    weSwapBuffers();
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
    weInit( argc, argv );
    weInitWindow( 500, 500, 0 );
    weInitOpenGL( 0 );
    weCreateWindow( "Moleculus" );
    weRenderFunc( render );
    weResizeFunc( resize );
    weKeyboardFunc( keyboard );
    init();
    weLoop();
    phys_free();;
    uiFontKill( &font );
    weFree( ver );
    weFree( vertex );
	return 0;
}

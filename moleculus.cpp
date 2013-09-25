#include "logics/main.h"
extern "C" {
    #include "engine/system.h"
    #include "engine/draw.h"
    #include "engine/font.h"
};

we_engine engine;
we_font font;

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

void init()
{
    static int count = 0;

    border = engine.proj.aspect - 2.0f;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);
    glEnable(GL_BLEND);

    font.size = 14;
    font.weight = WE_MEDIUM;
    font.name = "terminus";
    we_font_build(&font);

    aspect = engine.proj.aspect;
    aspect -= 0.05f*aspect;

    we_draw_vertex_init(32);

    if (count < 1) {
        phys_init(border, border, px, py);
        MAX_COUNT = phys_count();
        a = phys_point();
    }
    count++;
}

void keyboard(int *keycode)
{
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

    fps = we_getfps();

    glLineWidth(1.1f);
    for (int i = 0; i < MAX_COUNT; i++) {
        glColor3f(a[i].c.r, a[i].c.g, a[i].c.b);
        we_draw_alpha_circle3f(a[i].pos.x, a[i].pos.y, a[i].radius);
    }

    glDisable(GL_BLEND);

    draw_graph();

    glColor3f(1.0f, 1.0f, 1.0f);
    we_font_printf(&font, -aspect, aspect - 0.03f*aspect, "N: %d", MAX_COUNT);
    we_font_printf(&font, -aspect, aspect - 0.09f*aspect, "E: %.4f", phys_energy());
    we_font_printf(&font, -aspect, -aspect, "FPS: %.1f", fps);

    if (p_pause)
        we_font_printf(&font, -aspect, aspect - 0.15f*aspect, "paused");

    glEnable(GL_BLEND);

    phys_do();

    if (!p_pause)
        phys_move(dt);

    we_opengl_swapbuffers();
}

int main(int argc, char *argv[])
{
    engine.name = "Moleculus";
    engine.appclass = "ENGiNE";
    engine.width = 500;
    engine.height = 500;
    engine.fullscreen = 0;
    engine.argc = argc;
    engine.argv = argv;
    engine.max_fps = 60;
    engine.proj.angle = 0.0f;
    engine.proj.aspect = 60.0f;
    engine.proj.zFar = 100.0f;
    engine.proj.zNear = 1.0f;

    we_init(init);
    we_render(render);
    we_keyboard(keyboard);
    we_loop(&engine);

    phys_free();
    we_draw_vertex_free();
    we_font_kill();

    return 0;
}

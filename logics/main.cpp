#include "main.h"

static float ENERGY;                    // энергия системы
const float kf = 3.0f;                  // коэффициент расположения частиц
static float border_x = 56.0f;          // стандартная граница симуляции по x
static float border_y = 56.0f;          // стандартная граница симуляции по y

point *p;
rc config;

void phys_init(float xborder, float yborder, float px, float py)
{
    float p_x = -px;

    config = configure("config.txt");

    border_x = xborder;
    border_y = yborder;

    if (p != NULL)
        p = (point *) we_realloc(p, config.max_count * sizeof(point));
    else
           p = (point *) we_malloc(config.max_count * sizeof(point));

    for (int i = 0; i < config.max_count; i++) {
        p[i].pos = Vector2(px, py);
        if (config.start_speed > 0)
            p[i].vel = Vector2(
                    rand()%config.start_speed - config.start_speed/2.0f,
                    rand()%config.start_speed - config.start_speed/2.0f);
        else
            p[i].vel = Vector2(0.0f, 0.0f);

        p[i].acc = Vector2(0.0f, 0.0f);
        p[i].acc_1 = Vector2(0.0f, 0.0f);
        p[i].acc_2 = Vector2(0.0f, 0.0f);
        p[i].radius = config.radius;
        p[i].q = (i%2 - 0.5f);
        p[i].mass = 1;
        p[i].c = we_draw_color3f(0.0f, 0.5f, 1.0f);

        if (px < p_x - 2.0f)
            px += config.radius * kf;
        else {
            py += config.radius * kf;
            px = -p_x;
        }
    }
}

void phys_free()
{
    we_free(p);
}

void phys_do()
{
    for (int i = 0; i < config.max_count; i++) {
        if (config.borders) {
            int near_w, move_to_wall;
            /* удар о плоскость стенки, параллельной yOz */
            near_w = (fabs(p[i].pos.x) + p[i].radius) > border_x;
            move_to_wall = (p[i].vel.x * p[i].pos.x) > 0.0f;
            if (near_w && move_to_wall)
                p[i].vel.x = -p[i].vel.x;

            /* удар о плоскость стенки, параллельной xOz */
            near_w = (fabs(p[i].pos.y) + p[i].radius) > border_y;
            move_to_wall = (p[i].vel.y * p[i].pos.y) > 0.0f;
            if (near_w && move_to_wall)
                p[i].vel.y = -p[i].vel.y;
        }

        for (int j = i + 1; j < config.max_count; j++)
            phys_collide(i, j);
    }
}

void phys_move(float dt)
{
    for (int i = 0; i < config.max_count; i++)
        p[i].pos += p[i].vel * dt + p[i].acc * dt*dt/2.0f;

    for (int i = 0; i < config.max_count; i++)
    {
        p[i].vel = p[i].vel + p[i].acc * dt;
        p[i].acc = acceleration(i);

        if (config.check_energy)
            ENERGY += p[i].mass * (p[i].vel * p[i].vel) / 2.0f;
            if (config.ext_interaction == 2)
                ENERGY += p[i].mass * 10.0f * p[i].pos.y;
    }

    if (config.check_energy)
        ENERGY = ENERGY / config.max_count;
}

void phys_collide(int i, int j)
{
    float rad = p[i].radius + p[j].radius;
    Vector2 vi = p[i].vel, vj = p[j].vel;
    Vector2 delta = p[i].pos - p[j].pos;
    Vector2 n = delta.norm(); // для соударения -- вектор направления центров
    two_points ps;

    int before_contact = (vj - vi) * n > 0;
    int mass_exists = p[i].mass * p[j].mass > 0;      // наличие массы
    if ((delta.length() < rad) && before_contact && mass_exists)
    {
        switch (config.hit_type) {
            case 0:
                ps = elastic_collision(p[i], p[j]);
                p[i] = ps.fst;
                p[j] = ps.snd;
                break;
            case 1:
                ps = inelastic_collision(p[i], p[j]);
                p[i] = ps.fst;
                p[j] = ps.snd;
                break;
            case 2:
                ps = adhesion(p[i], p[j]);
                p[i] = ps.fst;
                p[j] = ps.snd;
                break;
        }
    }
}

int phys_count()
{
    return config.max_count;
}

float phys_energy()
{
    return ENERGY;
}

point * phys_point()
{
    return p;
}

void phys_border(float bx, float by)
{
    border_x = bx;
    border_y = by;
}

Vector2 acceleration(int i)
{
    Vector2 gravity, elect, r, acc;

    switch (config.ext_interaction)
    {
        case 0:
            acc = Vector2(0.0f, 0.0f);
            break;
        case 1:
            acc = Vector2(-p[i].pos.x, -p[i].pos.y);
            break;
        case 2:
            acc = Vector2(0.0f, -10.0f);
            break;
        default:
            printf("error: config.ext_interaction out of range [0,2]\n");
            break;
    }

    switch (config.interaction)
    {
        case 0:
            break;
        case 1:
            gravity = Vector2(0.0f, 0.0f);

            for (int j = 0; j < config.max_count; j++)
            {
                int not_into = (p[j].pos - p[i].pos).length() >
                    p[i].radius + p[j].radius;
                if (not_into && j != i)
                    gravity += newton_force(p[i], p[j]);
            }
            acc += gravity * config.G;
            break;
        case 2:
            elect = Vector2(0.0f, 0.0f);

            for (int j = 0; j < config.max_count; j++)
            {
                int not_into = (p[j].pos - p[i].pos).length() >
                    p[i].radius + p[j].radius;
                if (not_into && j != i)
                    elect += coulomb_force(p[i], p[j]);
            }
            acc += elect * config.E;
            break;
        case 3:
            elect = Vector2(0.0f, 0.0f);
            gravity = Vector2(0.0f, 0.0f);

            for (int j = 0; j < config.max_count; j++) {
                int not_into = (p[j].pos - p[i].pos).length() >
                    p[i].radius + p[j].radius;
                if (not_into) {
                    elect += coulomb_force(p[i], p[j]);
                    gravity += newton_force(p[i], p[j]);
                }
                acc += elect * config.E + gravity * config.G;
            }
            break;
        default:
            printf("error: config.interaction out of range [0,3]\n");
            break;
    }
    return acc;
}

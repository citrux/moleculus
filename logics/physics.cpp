#include "physics.h"

two_points elastic_collision(point p_i, point p_j)
{
    Vector2 n, m;
    Vector2 v_i = p_i.vel, v_j = p_j.vel;
    n = (p_j.pos - p_i.pos).norm();
    m.x = n.y;
    m.y = -n.x;
    // закон сохранения импульса при упругих соударениях:
    p_i.vel = ((n * ((p_i.mass - p_j.mass) * (v_i * n) + 
        2 * p_i.mass * (v_j * n)) / (p_i.mass + p_j.mass)) + (m * (v_i * m)));
    p_j.vel = ((n * ((p_j.mass - p_i.mass) * (v_j * n) +
        2 * p_j.mass * (v_i * n)) / (p_i.mass + p_j.mass)) + (m * (v_j * m)));
    two_points ps = {p_i, p_j};
    return ps;
}


two_points inelastic_collision(point p_i, point p_j)
{
    Vector2 n, m;
    Vector2 v_i = p_i.vel, v_j = p_j.vel;
    n = (p_j.pos - p_i.pos).norm();
    m.x = n.y;
    m.y = -n.x;
    p_i.vel = (n * (p_i.mass * (v_i * n) + p_j.mass * (v_j * n)) / (p_i.mass + p_j.mass)) + (m * (v_i * m));
    p_j.vel = (n * (p_i.mass * (v_i * n) + p_j.mass * (v_j * n)) / (p_i.mass + p_j.mass)) + (m * (v_j * m));
    two_points ps = {p_i, p_j};
    return ps;
}


two_points adhesion(point p_i, point p_j)
{
    Vector2 v_i = p_i.vel, v_j = p_j.vel;
    // закон сохранения импульса при неупругих соударениях:
    p_i.vel = ((v_i * p_i.mass) + (v_j * p_j.mass)) / (p_i.mass+p_j.mass);
    p_i.pos = ((p_i.pos * p_i.mass) + (p_j.pos * p_j.mass)) / (p_i.mass+p_j.mass);
    p_j.vel = Vector2(0.0, 0.0);
    p_i.mass = p_i.mass + p_j.mass;
    p_i.radius = sqrtf(p_i.mass);
    p_j.mass = 0;
    p_j.radius = 0;
    // p_i.q = p_i.q + p_j.q;
    // p_j.q = 0;
    two_points ps = {p_i, p_j};
    return ps;
}


Vector2 newton_force(point p_i, point p_j)
/* 
 сила гравитационного притяжения, действующая со стороны тела p_j на тело p_i
*/
{
    Vector2 r = p_j.pos - p_i.pos;
    return r * (p_j.mass / powf(r.length(), 3));
}

Vector2 coulomb_force(point p_i, point p_j)
/* 
 кулоновская сила, действующая со стороны тела p_j на тело p_i
*/
{
    Vector2 r = p_j.pos - p_i.pos;
    return r * (-p_j.q / powf(r.length(), 3));
}

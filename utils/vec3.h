#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct vec3
{
    double e[3];
};

typedef struct vec3 vec3;

vec3 make_vec3(double e0, double e1, double e2)
{
    vec3 v;
    v.e[0] = e0;
    v.e[1] = e1;
    v.e[2] = e2;
    return v;
}

double x_from(const vec3 *v)
{
    return v->e[0];
}

double y_from(const vec3 *v)
{
    return v->e[1];
}

double z_from(const vec3 *v)
{
    return v->e[2];
}

vec3 neg_from(const vec3 *v)
{
    return make_vec3(-v->e[0], -v->e[1], -v->e[2]);
}

double get_from(const vec3 *v, int i)
{
    if (i < 2)
    {
        return v->e[i];
    }
    else
    {
        exit(1);
    }
}

void set_to(vec3 *v, int i, double value)
{
    v->e[i] = value;
}

void print_vec(vec3 *v)
{
    double x = x_from(v);
    double y = y_from(v);
    double z = z_from(v);

    fprintf(stderr, "\rX: %f Y: %f Z: %f \n", x, y, z);
}

vec3 scale_to(const vec3 *v, double scale)
{
    double r = v->e[0] * scale;
    double g = v->e[1] * scale;
    double b = v->e[2] * scale;

    return make_vec3(r, g, b);
}

vec3 div_by_scalar_to(const vec3 *v, double scale)
{
    double r = v->e[0] / scale;
    double g = v->e[1] / scale;
    double b = v->e[2] / scale;
    return make_vec3(r, g, b);
}

double length_squared_of(const vec3 *v)
{
    double x = v->e[0] * v->e[0];
    double y = v->e[1] * v->e[1];
    double z = v->e[2] * v->e[2];
    return x + y + z;
}

double length_of(const vec3 *v)
{
    double length = length_squared_of(v);
    return sqrt(length);
}

typedef vec3 point3;

void print_vec3(const vec3 *v)
{
    fprintf(stderr, "%f %f %f", v->e[0], v->e[1], v->e[2]);
}

vec3 add_to(vec3 *v, const vec3 *v2)
{
    double r = v->e[0] + v2->e[0];
    double g = v->e[1] + v2->e[1];
    double b = v->e[2] + v2->e[2];
    return make_vec3(r, g, b);
}

vec3 substract_to(const vec3 *v, const vec3 *v2)
{
    double r = v->e[0] - v2->e[0];
    double g = v->e[1] - v2->e[1];
    double b = v->e[2] - v2->e[2];

    return make_vec3(r, g, b);
}

vec3 multiply_to(const vec3 *v, const vec3 *v2)
{
    double r = v->e[0] * v2->e[0];
    double g = v->e[1] * v2->e[1];
    double b = v->e[2] * v2->e[2];

    return make_vec3(r, g, b);
}

double dot_product(const vec3 *v, const vec3 *u)
{
    double x = v->e[0] * u->e[0];
    double y = v->e[1] * u->e[1];
    double z = v->e[2] * u->e[2];

    return x + y + z;
}

vec3 cross_product_to(const vec3 *u, const vec3 *v)
{
    double r = u->e[1] * v->e[2] - u->e[2] * v->e[1];
    double g = u->e[2] * v->e[0] - u->e[0] * v->e[2];
    double b = u->e[0] * v->e[1] - u->e[1] * v->e[0];

    return make_vec3(r, g, b);
}

vec3 unit_vector(const vec3 *v)
{
    double len = length_of(v);
    return div_by_scalar_to(v, len);
}

#endif

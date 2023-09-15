#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ray.h"

#include <stdio.h>
#include <stdbool.h>

#include "shapes/sphere.h"

typedef vec3 color;

color make_color(double r, double g, double b)
{
    return make_vec3(r, g, b);
}

double hit_sphere(const point3 *center, double radius, const ray *r)
{
    vec3 oc = substract_to(&r->orig, center);
    double a = length_squared_of(&r->dir);
    double half_b = dot_product(&oc, &r->dir);
    double c = length_squared_of(&oc) - radius * radius;

    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant) / a);
    }
}

void write_color(color pixel_color)
{
    double x = x_from(&pixel_color);
    double y = y_from(&pixel_color);
    double z = z_from(&pixel_color);

    int r = (int)(255.999 * x);
    int g = (int)(255.999 * y);
    int b = (int)(255.999 * z);

    printf("%d %d %d\n", r, g, b);
}

#endif
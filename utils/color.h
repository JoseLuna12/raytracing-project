#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ray.h"
#include "../shapes/sphere.h"

#include <stdio.h>
#include <stdbool.h>

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

color make_color_from_ray(ray *r)
{
    point3 center = make_vec3(0, 0, -1);
    double hit_sphere_result = hit_sphere(&center, 0.5, r);

    if (hit_sphere_result > 0.0)
    {
        point3 ray_at_value = ray_at(r, hit_sphere_result);
        vec3 n_subtract = substract_to(&ray_at_value, &center);
        vec3 N = unit_vector(&n_subtract);
        color color_to_return = make_color(x_from(&N) + 1, y_from(&N) + 1, z_from(&N) + 1);

        return scale_to(&color_to_return, 0.5);
    }

    vec3 unit_direction = unit_vector(&r->dir);

    double y = y_from(&unit_direction);
    double a = 0.5 * (y + 1.0);

    color color_one = make_color(1.0, 1.0, 1.0);
    color colort_two = make_color(0.5, 0.7, 1.0);

    color times_color_one = scale_to(&color_one, 1.0 - a);
    color times_color_two = scale_to(&colort_two, a);

    return add_to(&times_color_one, &times_color_two);
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
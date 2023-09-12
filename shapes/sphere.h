#ifndef SPHERE_H
#define SPHERE_H

#include "../utils/hittable.h"
#include "../utils/vec3.h"

#include <stdbool.h>

typedef struct sphere
{
    hittable base;
    point3 center;
    double radius;
} sphere;

bool sphere_hit(const hittable *obj, const ray *r, double ray_t_min, double ray_t_max, hit_record *rec)
{
    const sphere *s = (const sphere *)obj;
    vec3 oc = substract_to(&r->orig, &s->center);
    double a = length_squared_of(&r->dir);
    double half_b = dot_product(&oc, &r->dir);
    double c = length_squared_of(&oc) - s->radius * s->radius;

    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return false;
    }

    double sqrtd = sqrt(discriminant);

    double root = (-half_b - sqrtd) / a;
    if (root <= ray_t_min || ray_t_max <= root)
    {
        root = (-half_b + sqrtd) / a;
        if (root <= ray_t_min || ray_t_max <= root)
        {
            return false;
        }
    }

    rec->t = root;
    rec->p = ray_at((ray *)r, rec->t);

    vec3 normal_substract = substract_to(&rec->p, &s->center);
    rec->normal = div_by_scalar_to(&normal_substract, s->radius);

    return true;
}

sphere make_sphere(point3 center, double radius)
{
    hittable hittable_var;
    hittable_var.vtable = sphere_hit;

    sphere s;
    s.base = hittable_var;
    s.center = center;
    s.radius = radius;
    return s;
}

#endif

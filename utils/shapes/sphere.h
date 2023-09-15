#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>
#include "../hittable.h"
#include "../vec3.h"
#include "shapes.h"

bool hit_hittable_sphere(hittable_shape *obj, ray *r, double ray_tmin, double ray_tmax, hit_record *rec)
{
    const Sphere *s = (Sphere *)obj;
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
    if (root <= ray_tmin || ray_tmax <= root)
    {
        root = (-half_b + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
        {
            return false;
        }
    }

    rec->t = root;
    rec->p = ray_at(r, rec->t);
    vec3 outward_normal_sub = substract_to(&rec->p, &s->center);
    vec3 outward_normal = div_by_scalar_to(&outward_normal_sub, s->radius);

    rec->normal = set_face_normal_of(r, &outward_normal);
    return true;
}

hittable make_sphere(point3 center, double radius)
{
    Sphere sphere = {
        center,
        radius,
    };

    hittable hittable_sphere = {
        .shape = sphere,
        .hit = hit_hittable_sphere,
    };

    return hittable_sphere;
}

#endif

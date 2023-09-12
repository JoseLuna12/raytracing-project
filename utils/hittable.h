#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include <stdbool.h>

typedef struct
{
    point3 p;
    vec3 normal;
    double t;
} hit_record;

typedef struct hittable hittable;

typedef struct
{
    bool (*hit)(const hittable *obj, const ray *r, double ray_t_min, double ray_t_max, hit_record *rec);
} hittable_vtable;

struct hittable
{
    const hittable_vtable *vtable;
};

bool hit(const hittable *obj, const ray *r, double ray_t_min, double ray_t_max, hit_record *rec)
{
    return obj->vtable->hit(obj, r, ray_t_min, ray_t_max, rec);
}

#endif
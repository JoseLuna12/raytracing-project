#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "ray.h"
#include "shapes/shapes.h"
#include "interval.h"

typedef struct hit_record
{
    point3 p;
    vec3 normal;
    double t;
    bool front_face;

} hit_record;

vec3 set_face_normal_of(const ray *r, const vec3 *outward_normal)
{
    bool front_face_value = dot_product(&r->dir, outward_normal) < 0;
    vec3 outward_normal_negative = neg_from(outward_normal);
    if (front_face_value)
    {
        return scale_to(outward_normal, 1);
    }
    return outward_normal_negative;
}

typedef union
{
    Sphere sphere;
} hittable_shape;

typedef struct hittable
{
    hittable_shape shape;
    bool (*hit)(hittable_shape *obj, ray *r, interval *ray_t, hit_record *rec);
} hittable;

typedef struct HittableList
{
    hittable **objects;
    size_t size;
    bool (*hit)(struct HittableList *obj, ray *r, interval *ray_t, hit_record *rec);
} HittableList;

#endif
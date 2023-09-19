#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <stdbool.h>
#include "interval.h"

bool hit_hittable_list(HittableList *obj, ray *r, interval *ray_t, hit_record *rec)
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t->max;

    for (size_t i = 0; i < obj->size; i++)
    {
        hittable_shape shape = obj->objects[i]->shape;
        interval sphere_interval = {ray_t->min, closest_so_far};
        if (obj->objects[i]->hit(&shape, r, &sphere_interval, &temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

HittableList *create_hittable_list(size_t size)
{
    HittableList *list = malloc(sizeof(HittableList));

    list->objects = malloc(size);
    list->size = size;
    list->hit = hit_hittable_list;
    return list;
}

void add_hittable_to_list(HittableList *list, hittable *object, size_t position)
{
    list->objects[position] = object;
}

void clear_hittable_list(HittableList *list)
{
    if (list->objects)
    {
        free(list->objects);
    }
    free(list);
}

#endif
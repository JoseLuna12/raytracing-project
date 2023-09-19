#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "color.h"
#include "hittable.h"

typedef struct camera
{
    double aspect_ratio;
    int image_width;
    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
} camera;

camera *init_camera(double aspect_ratio, int image_width)
{
    camera *cam = (camera *)malloc(sizeof(camera));
    if (!cam)
    {
        fprintf(stderr, "Failed to allocate memory for the camera.\n");
        exit(EXIT_FAILURE);
    }

    int image_height = (int)(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    cam->aspect_ratio = aspect_ratio;
    cam->image_width = image_width;
    cam->image_height = image_height;
    cam->center = make_vec3(0, 0, 0);

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)cam->image_width / (double)cam->image_height);

    vec3 viewport_u = make_vec3(viewport_width, 0, 0);
    vec3 viewport_v = make_vec3(0, -viewport_height, 0);

    cam->pixel_delta_u = div_by_scalar_to(&viewport_u, image_width);
    cam->pixel_delta_v = div_by_scalar_to(&viewport_v, cam->image_height);

    vec3 half_viewport_u = div_by_scalar_to(&viewport_u, 2);
    vec3 half_viewport_v = div_by_scalar_to(&viewport_v, 2);
    vec3 partial_focal_length = make_vec3(0, 0, focal_length);
    vec3 camera_substraction = substract_to(&cam->center, &partial_focal_length);
    vec3 camera_minus_viweport_u = substract_to(&camera_substraction, &half_viewport_u);
    vec3 viewport_upper_left = substract_to(&camera_minus_viweport_u, &half_viewport_v);

    vec3 pixel_delta_u_scale = scale_to(&cam->pixel_delta_u, 0.5);
    vec3 pixel_delta_v_scale = scale_to(&cam->pixel_delta_v, 0.5);
    vec3 pixel_delta_sum = add_to(&pixel_delta_u_scale, &pixel_delta_v_scale);

    cam->pixel00_loc = add_to(&viewport_upper_left, &pixel_delta_sum);

    return cam;
}

color ray_color_maker(ray *r, HittableList *world)
{
    hit_record rec;
    interval world_interval = {0, infinity};
    if (world->hit(world, r, &world_interval, &rec))
    {
        color sphere_color = make_color(1, 1, 1);
        color sum_rec_normal = add_to(&rec.normal, &sphere_color);
        return scale_to(&sum_rec_normal, 0.5);
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

void camera_render(camera *cam, HittableList *world)
{

    printf("P3 \n%d %d\n255\n", cam->image_width, cam->image_height);
    for (int j = 0; j < cam->image_height; ++j)
    {
        fprintf(stderr, "\rScan lines remaining %d", (cam->image_height - j));
        for (int i = 0; i < cam->image_width; ++i)
        {

            vec3 pixel_delta_u_times = scale_to(&cam->pixel_delta_u, i);
            vec3 pixel_delta_v_times = scale_to(&cam->pixel_delta_v, j);
            vec3 pixel_sum = add_to(&pixel_delta_u_times, &pixel_delta_v_times);

            vec3 pixel_center = add_to(&cam->pixel00_loc, &pixel_sum);
            vec3 ray_direction = substract_to(&pixel_center, &cam->center);

            ray r = make_ray(&cam->center, &ray_direction);

            color pixel_color = ray_color_maker(&r, world);
            write_color(pixel_color);
        }
        fflush(stderr);
    }
}

#endif
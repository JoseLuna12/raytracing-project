#include "utils/camera.h"
#include "utils/color.h"
#include "utils/rtweekend.h"
#include "utils/hittable.h"
#include "utils/hittable_list.h"
#include "utils/shapes/sphere.h"

#include <stdio.h>

// color ray_color_maker(ray *r, HittableList *world)
// {
//     hit_record rec;
//     interval world_interval = {0, infinity};
//     if (world->hit(world, r, &world_interval, &rec))
//     {
//         color sphere_color = make_color(1, 1, 1);
//         color sum_rec_normal = add_to(&rec.normal, &sphere_color);
//         return scale_to(&sum_rec_normal, 0.5);
//     }
//     vec3 unit_direction = unit_vector(&r->dir);

//     double y = y_from(&unit_direction);
//     double a = 0.5 * (y + 1.0);

//     color color_one = make_color(1.0, 1.0, 1.0);
//     color colort_two = make_color(0.5, 0.7, 1.0);

//     color times_color_one = scale_to(&color_one, 1.0 - a);
//     color times_color_two = scale_to(&colort_two, a);

//     return add_to(&times_color_one, &times_color_two);
// }

int main()
{
    // image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // end image

    // world
    HittableList *world = create_hittable_list(2);

    point3 sphere_one_center = make_vec3(0, 0, -1);
    hittable sphere_one = make_sphere(sphere_one_center, 0.5);

    point3 sphere_two_center = make_vec3(0, -100.5, -1);
    hittable sphere_two = make_sphere(sphere_two_center, 100);

    add_hittable_to_list(world, &sphere_one, 1);
    add_hittable_to_list(world, &sphere_two, 0);

    camera *cam = init_camera(16.0 / 9.0, 400);

    camera_render(cam, world);
}
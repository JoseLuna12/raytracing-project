#include "utils/color.h"
#include "utils/vec3.h"
#include "utils/ray.h"

#include <stdio.h>

int main()
{
    // image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // end image

    // camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / (double)image_height);
    point3 camera_center = make_vec3(0, 0, 0);

    // viewport horizontal and vertical vectors
    vec3 viewport_u = make_vec3(viewport_width, 0, 0);
    vec3 viewport_v = make_vec3(0, -viewport_height, 0);

    // distance from pixel to pixel
    vec3 pixel_delta_u = div_by_scalar_to(&viewport_u, image_width);
    vec3 pixel_delta_v = div_by_scalar_to(&viewport_v, image_height);

    // viewport calculation
    vec3 half_viewport_u = div_by_scalar_to(&viewport_u, 2);
    vec3 half_viewport_v = div_by_scalar_to(&viewport_v, 2);
    vec3 partial_focal_length = make_vec3(0, 0, focal_length);
    vec3 camera_substraction = substract_to(&camera_center, &partial_focal_length);
    vec3 camera_minus_viweport_u = substract_to(&camera_substraction, &half_viewport_u);
    vec3 viewport_upper_left = substract_to(&camera_minus_viweport_u, &half_viewport_v);
    // view port calculation

    // pixel 00 calculation
    vec3 pixel_delta_u_scale = scale_to(&pixel_delta_u, 0.5);
    vec3 pixel_delta_v_scale = scale_to(&pixel_delta_v, 0.5);
    vec3 pixel_delta_sum = add_to(&pixel_delta_u_scale, &pixel_delta_v_scale);
    vec3 pixel00_loc = add_to(&viewport_upper_left, &pixel_delta_sum);
    // pixel 00 calculation

    // end camera

    printf("P3 \n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j)
    {
        fprintf(stderr, "\rScan lines remaining %d ", (image_height - j));
        for (int i = 0; i < image_width; ++i)
        {

            vec3 pixel_delta_u_times = scale_to(&pixel_delta_u, i);
            vec3 pixel_delta_v_times = scale_to(&pixel_delta_v, j);
            vec3 pixel_sum = add_to(&pixel_delta_u_times, &pixel_delta_v_times);

            vec3 pixel_center = add_to(&pixel00_loc, &pixel_sum);
            vec3 ray_direction = substract_to(&pixel_center, &camera_center);

            ray r = make_ray(&camera_center, &ray_direction);

            color pixel_color = make_color_from_ray(&r);
            write_color(pixel_color);
        }
        fflush(stderr);
    }
}
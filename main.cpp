/*
 * Follows the Ray Tracing in One Weekend book:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview
 */

#include "rtweekend.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"


int main() {
    hittable_list world;

    auto material_ground = std::make_shared<lambertian>(color(0.9, 0.7, 0.46));
    auto material_center = std::make_shared<lambertian>(color(0.5, 0.24, 0.1));
    auto material_left   = std::make_shared<dielectric>(1.50, color(0.1, 0.5, 0.7));
    auto material_bubble = std::make_shared<dielectric>(1.00 / 1.50, color(1, 1, 1));
    auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));


    camera cam;

    cam.aspect_ratio = 16.0 / 9;
    cam.image_width = 1280;
    cam.samples_per_pixel = 420;
    cam.max_depth = 50;
    cam.vfov = 35;

    cam.lookfrom = point3(-2, 2, 1);
    cam.lookat = point3(0, 0, -1);
    cam.vup = vec3(0, 1, -0.1);
    cam.vup /= cam.vup.length();  // normalize

    cam.render(world);

    return 0;
}

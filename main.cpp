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

    auto material_ground = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    auto material_blue_diamond = std::make_shared<dielectric>(2.4, color(0.72, 0.95, 1));
    auto material_blue_glass   = std::make_shared<dielectric>(1.50, color(0.1, 0.5, 0.7));
    auto material_green_glass   = std::make_shared<dielectric>(1.50, color(0.56 * 1.2, 0.78 * 1.2, 0.7 * 1.2));
    auto material_clear_glass   = std::make_shared<dielectric>(1.50, color(1, 1, 1));
    auto material_blue_diamond_bubble   = std::make_shared<dielectric>(2.4 / 1.5, color(0.72, 0.95, 1));
    auto material_glass_bubble = std::make_shared<dielectric>(1.00 / 1.50, color(1, 1, 1));
    auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -3),   0.5, material_green_glass));
    world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -3),   0.4, material_glass_bubble));
    world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -5),   0.6, material_blue_diamond));

    camera cam;

    cam.aspect_ratio = 16.0 / 9;
    cam.image_width = 800;
    cam.samples_per_pixel = 300;
    cam.max_depth = 50;

    cam.vfov = 35;
    cam.lookfrom = point3(-1, 0, 0);
    cam.lookat = point3(0, 0, -4);
    cam.vup = vec3(0, 1, 0);
    cam.vup /= cam.vup.length();  // normalize

    cam.defocus_angle = 2;
    cam.focus_dist = 3;

    cam.render(world);

    return 0;
}

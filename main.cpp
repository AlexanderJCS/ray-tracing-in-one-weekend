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

    std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.8));
    std::shared_ptr<lambertian> material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    std::shared_ptr<dielectric> material_left = std::make_shared<dielectric>(1.5);
    std::shared_ptr<dielectric> material_bubble = std::make_shared<dielectric>(1 / 1.5);
    std::shared_ptr<metal> material_right = std::make_shared<metal>(color(0.8, 0.0, 0.2), 1);

    world.add(std::make_shared<sphere>(point3( 0, -100.5, -1), 100, material_ground));
    world.add(std::make_shared<sphere>(point3( 0, 0, -1.2), 0.5, material_center));
    world.add(std::make_shared<sphere>(point3( -1, 0, -1), 0.5, material_left));
    world.add(std::make_shared<sphere>(point3( -1, 0, -1), 0.4, material_bubble));
    world.add(std::make_shared<sphere>(point3( 1, 0, -1), 0.5, material_right));

    camera cam;

    cam.aspect_ratio = 16.0 / 9;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 100;

    cam.render(world);

    return 0;
}

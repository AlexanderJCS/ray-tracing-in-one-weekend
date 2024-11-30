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
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

    camera cam;

    cam.aspect_ratio = 16.0 / 9;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 100;

    cam.render(world);

    return 0;
}

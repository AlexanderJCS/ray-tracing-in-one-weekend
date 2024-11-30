/*
 * Follows the Ray Tracing in One Weekend book:
 * https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"
#include "ray.h"
#include "color.h"


double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();  // ray origin to sphere center

    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - radius * radius;

    double discriminant = h * h - a * c;

    if (discriminant < 0) {
        return -1;
    }

    // return the distance to the hit point
    return (h - std::sqrt(discriminant)) / a;
}


color ray_color(const ray& r) {
    point3 sphere_center{0, 0, -1};

    double t = hit_sphere(sphere_center, 0.5, r);
    if (t > 0) {
        vec3 normal = unit_vector(r.at(t) - sphere_center);
        return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vec3 unit_dir = unit_vector(r.direction());
    double a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a ) * color(1, 1, 1) + a * color(0.5, 0.7, 1);
}


int main() {
    double aspect_ratio = 16.0 / 9;

    int image_width = 400;
    int image_height = std::max(int(image_width / aspect_ratio), 1);

    double focal_length = 1;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(image_width) / image_height);
    point3 camera_center{0, 0, 0};

    vec3 viewport_u{viewport_width, 0, 0};
    vec3 viewport_v{0, -viewport_height, 0};

    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

    point3 viewport_upper_left = camera_center - vec3{0, 0, focal_length} - viewport_u / 2 - viewport_v / 2;
    point3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::ofstream output{"../output.ppm"};
    if (!output) {
        std::cerr << "Cannot open file. Exiting\n";
        exit(1);
    }

    output << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::cout << "Scanlines remaining: " << (image_height - j) << std::endl;

        for (int i = 0; i < image_width; i++) {
            vec3 pixel_center = pixel00_loc + (i * pixel_delta_u + j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            ray r{camera_center, ray_direction};
            color pixel_color = ray_color(r);
            write_color(output, pixel_color);
        }
    }

    std::cout << "Done" << std::endl;

    output.close();

    return 0;
}

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <fstream>

#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    void render(const hittable& world) {
        initialize();

        std::ofstream output{"../output.ppm"};
        if (!output) {
            std::cerr << "Cannot open file. Exiting\n";
            exit(1);
        }

        output << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::cout << "Scanlines remaining: " << (image_height - j) << std::endl;

            for (int i = 0; i < image_width; i++) {
                color pixel_color(0, 0, 0);

                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }

                write_color(output, pixel_color / samples_per_pixel);
            }
        }

        std::cout << "Done" << std::endl;

        output.close();
    }

private:
    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize() {
        image_height = std::max(int(image_width / aspect_ratio), 1);

        double focal_length = 1;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * (double(image_width) / image_height);
        center = point3(0, 0, 0);

        vec3 viewport_u{viewport_width, 0, 0};
        vec3 viewport_v{0, -viewport_height, 0};

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        point3 viewport_upper_left = center - vec3{0, 0, focal_length} - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    [[nodiscard]] ray get_ray(int i, int j) const {
        vec3 offset = sample_square();
        vec3 pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);
        vec3 ray_direction = pixel_sample - center;

        return {center, ray_direction};
    }

    [[nodiscard]] static vec3 sample_square() {
        return {random_double() - 0.5, random_double() - 0.5, 0};
    }

    [[nodiscard]] static color ray_color(const ray& r, int depth, const hittable& world) {
        if (depth <= 0) {
            return color(0, 0, 0);
        }

        hit_record rec;

        if (world.hit(r, interval(0.001, infinity), rec)) {
            vec3 direction = rec.normal + random_unit_vector();
            return 0.5 * ray_color(ray(rec.p, direction), depth - 1, world);
        }

        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1);
        return (1 - a) * color(1, 1, 1) + a * color(0.5, 0.7, 1);
    }
};

#endif  // RAY_TRACER_CAMERA_H

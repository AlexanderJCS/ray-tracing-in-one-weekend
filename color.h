#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }

    return 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
    static const interval intensity(0, 0.999);

    out << int(256 * intensity.clamp(linear_to_gamma(pixel_color.x()))) << ' '
        << int(256 * intensity.clamp(linear_to_gamma(pixel_color.y()))) << ' '
        << int(256 * intensity.clamp(linear_to_gamma(pixel_color.z()))) << '\n';
}

#endif  // RAY_TRACER_COLOR_H

#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    static const interval intensity(0, 0.999);

    out << int(256 * intensity.clamp(pixel_color.x())) << ' '
        << int(256 * intensity.clamp(pixel_color.y())) << ' '
        << int(256 * intensity.clamp(pixel_color.z())) << '\n';
}

#endif  // RAY_TRACER_COLOR_H

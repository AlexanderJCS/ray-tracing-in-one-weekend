#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include "vec3.h"

#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    out << int(255.999 * pixel_color.x()) << ' '
        << int(255.999 * pixel_color.y()) << ' '
        << int(255.999 * pixel_color.z()) << '\n';
}

#endif  // RAY_TRACER_COLOR_H

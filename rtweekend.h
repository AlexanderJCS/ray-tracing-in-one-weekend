#ifndef RAY_TRACER_RTWEEKEND_H
#define RAY_TRACER_RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = std::numbers::pi;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif  // RAY_TRACER_RTWEEKEND_H

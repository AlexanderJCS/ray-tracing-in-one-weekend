#ifndef RAY_TRACER_RTWEEKEND_H
#define RAY_TRACER_RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = std::numbers::pi;

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180;
}

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(std::random_device{}());
    return distribution(generator);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif  // RAY_TRACER_RTWEEKEND_H

#ifndef RAY_TRACER_INTERVAL_H
#define RAY_TRACER_INTERVAL_H


class interval {
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}

    [[nodiscard]] double size() const {
        return max - min;
    }

    [[nodiscard]] bool contains(double x) const {
        return x >= min && x <= max;
    }

    [[nodiscard]] bool surrounds(double x) const {
        return x > min && x < max;
    }

    [[nodiscard]] double clamp(double x) const {
        if (x < min) {
            return min;
        } if (x > max) {
            return max;
        }

        return x;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif  // RAY_TRACER_INTERVAL_H

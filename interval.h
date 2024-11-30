#ifndef RAY_TRACER_INTERVAL_H
#define RAY_TRACER_INTERVAL_H


class interval {
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    bool contains(double x) {
        return x >= min && x <= max;
    }

    bool surrounds(double x) const {
        return x > min && x < max;
    }

    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif  // RAY_TRACER_INTERVAL_H

#ifndef COMMONH
#define COMMONH

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

// Sabitler proje header'larindan ONCE tanimlanmali (interval.h infinity kullaniyor)
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

#include "vec3.h"
#include "interval.h"
#include "color.h"
#include "ray.h"

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // [0, 1)
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // [min, max)
    return min + (max-min)*random_double();
}




#endif
#ifndef HITTABLEH  
#define HITTABLEH

#include "ray.h"
#include <optional>

struct hit_record{
        point3 p;
        vec3 normal;
        double t;
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual std::optional<hit_record>  hit(const ray& r, double ray_tmin, double ray_tmax) const = 0;
};


#endif
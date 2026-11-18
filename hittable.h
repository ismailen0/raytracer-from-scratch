#ifndef HITTABLEH  
#define HITTABLEH

#include <optional>
#include "common.h"
struct hit_record{
        point3 p;
        vec3 normal;
        double t;

        void set_face_normal(const ray& r, const vec3& outward_normal) {
            bool front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;
        virtual std::optional<hit_record>  hit(const ray& r, interval ray_t) const = 0;
};


#endif
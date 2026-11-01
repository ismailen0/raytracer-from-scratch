#ifndef HITTABLEH  
#define HITTABLEH
#include "hittable.h"

class sphere : public hittable {
private:
    point3 center;
    double radius;

public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0,radius)) {}
        std::optional<hit_record> hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
                vec3 oc = center - r.origin();
                auto a = r.direction().length_squared();
                auto h = dot(r.direction(), oc);;
                auto c = oc.length_squared() - radius*radius;
                auto discriminant = h*h -a*c;
                if (discriminant < 0) return std::nullopt;        
                auto sqrtd = std::sqrt(discriminant);
                auto t1 = (h - sqrtd) / a;
                auto t2 = (h + sqrtd) / a;
               
                bool isT1Valid=(t1>=ray_tmin && t1 <= ray_tmax);
                bool isT2Valid = (t2>=ray_tmin && t2 <= ray_tmax);

                if(!isT1Valid && !isT2Valid) return std::nullopt;

                double root = (isT1Valid) ? t1 : t2;
                hit_record hr{};
                hr.p = r.at(root);
                // note about that: 
                // since p-center should be radius then we can easliy get cheap normal via division of rad
                hr.normal = (hr.p-this->center)/radius;
                hr.t = root;
                return hr;
        }


};

#endif
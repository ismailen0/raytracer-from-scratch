#ifndef HITTABLELISTH
#define HITTABLELISTH
#include "hittable.h"
#include <optional>
#include <memory>
#include <vector>
using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }
        
        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }
        std::optional<hit_record> hit(const ray& r, double ray_tmin, double ray_tmax) const override { 
            std::optional<hit_record> closest;
            auto closest_so_far = ray_tmax;
            for (const auto& object : objects) {
                if (auto temp_rec = object->hit(r, ray_tmin, closest_so_far)) {
                    closest_so_far = temp_rec->t;
                    closest = temp_rec;
                }
            }
            return closest;
    }
};
#endif






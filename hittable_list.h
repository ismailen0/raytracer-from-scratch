#ifndef HITTABLELISTH
#define HITTABLELISTH
#include "hittable.h"
#include <optional>
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
        std::optional<hit_record> hit(const ray& r, interval ray_t) const override { 
            std::optional<hit_record> closest;
            for (const auto& object : objects) {
                if (auto temp_rec = object->hit(r, ray_t)) {
                    ray_t.max = temp_rec->t;
                    closest = temp_rec;
                }
            }
            return closest;
    }
};
#endif






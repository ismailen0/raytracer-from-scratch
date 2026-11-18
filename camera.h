#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
  public:
    double aspect_ratio = 1.0; 
    int    i_width  = 100;
    int    samples_per_pixel = 10;  // antialiasing samples per pixel
    void render(const hittable& world) {
        initialize();

        std::cout << "P3" << std::endl << i_width << " " << i_height << std::endl << 255 << std::endl;
        for(int j = 0; j < i_height; j++){
            for(int i = 0; i < i_width; i++){
                color pixel_color(0,0,0);
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, world);
                }
                write_color(std::cout, pixel_samples_scale * pixel_color);
            }
        } 
    }

  private:
    int    i_height;  
    point3 camera_center;        
    point3 pixel00_loc;   
    vec3   pixel_delta_u; 
    vec3   pixel_delta_v;
    double pixel_samples_scale; 
    void initialize() {
    pixel_samples_scale = 1.0 / samples_per_pixel;
    // Since width and height should be integer we cannot get the real exact value of aspect ratiot
    // this is too imporant while we are dealing with viewport we'll use width/height
    i_height = static_cast<int>(i_width / aspect_ratio);
    i_height = (i_height < 1) ? 1 : i_height;

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(i_width)/i_height);
    
    auto focal_lenght = 1.0;
    camera_center = point3(0,0,0);

    auto viewport_u = vec3(viewport_width,0,0);
    // We are setting viewport height minus because we need to go down.
    auto viewport_v = vec3(0,-viewport_height,0);
    // delta_u and delta_v is an step that we need to go in loop
    pixel_delta_u = viewport_u / i_width;
    pixel_delta_v = viewport_v / i_height;

    // Since we are looking -z we need to substract focal_lenght in order to go on viewport
    auto viewport_upper_left = camera_center - vec3(0,0,focal_lenght);
    // now we are at the center of the viewport
    // now we need to go left how can we go left since we are now in the center via;
    viewport_upper_left = viewport_upper_left-(viewport_u/2);
    // now we are center left but we need to go upper left so lets divide height too and get that value and substract them so that
    viewport_upper_left = viewport_upper_left-(viewport_v/2);
    // now our starting point will be center of first square
    pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

    }

    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc
                          + ((i + offset.x()) * pixel_delta_u)
                          + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }
    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    color ray_color(const ray& r, const hittable& world) {
        if (auto rec = world.hit(r, interval(0, infinity))) {
            return 0.5 * (rec->normal + color(1,1,1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

};

#endif
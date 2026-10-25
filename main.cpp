#include <iostream>
#include "ray.h"
#include "color.h"
#include "vec3.h"


color ray_color(const ray& ray){
    auto ray_unit = unit_vector(ray.direction());
    
    // our value is now between -1 and +1 so we need to add +1 and divide by 2
    auto a = 0.5*(ray_unit.y()+1.0);
    // now If our a is 1 = white will not be accounted because of
    // 1.0-1
    // but If we have a is 0 now blue is not be accounted. 
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}


int main(){
    double aspect_ratio = 16.0 / 9.0;
    const int i_width = 400;
    // Since width and height should be integer we cannot get the real exact value of aspect ratiot
    // this is too imporant while we are dealing with viewport we'll use width/height
    int i_height = static_cast<int>(i_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(i_width)/i_height);
    i_height = (i_height < 1) ? 1 : i_height;

    auto focal_lenght = 1.0;
    auto camera_center = point3(0,0,0);

    auto viewport_u = vec3(viewport_width,0,0);
    // We are setting viewport height minus because we need to go down.
    auto viewport_v = vec3(0,-viewport_height,0);
    // delta_u and delta_v is an step that we need to go in loop
    auto pixel_delta_u = viewport_u / i_width;
    auto pixel_delta_v = viewport_v / i_height;

    // Since we are looking -z we need to substract focal_lenght in order to go on viewport
    auto viewport_upper_left = camera_center - vec3(0,0,focal_lenght);
    // now we are at the center of the viewport
    // now we need to go left how can we go left since we are now in the center via;
    viewport_upper_left = viewport_upper_left-(viewport_u/2);
    // now we are center left but we need to go upper left so lets divide height too and get that value and substract them so that
    viewport_upper_left = viewport_upper_left-(viewport_v/2);
    // now our starting point will be center of first square
    auto pixel00_loc = viewport_upper_left + 0.5*(pixel_delta_u + pixel_delta_v);

    std::cout << "P3" << std::endl << i_width << " " << i_height << std::endl << 255 << std::endl;
    for(int j = 0; j < i_height; j++){
        for(int i = 0; i < i_width; i++){
            auto pixel_center = pixel00_loc + (j*pixel_delta_v) + (i*pixel_delta_u);
            auto ray_direction = pixel_center-camera_center;
            ray r(camera_center,ray_direction);
            color pixel_color = ray_color(r);
            write_color(std::cout,pixel_color);
        }
    } 




}
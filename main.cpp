#include <iostream>


int main(){

    constexpr int i_width = 256;
    constexpr int i_height = 256;

    std::cout << "P3" << std::endl << i_width << " " << i_height << std::endl << 255 << std::endl;
    for(int j = 0; j < i_height; j++){
        for(int i = 0; i < i_width; i++){
            auto r = static_cast<double>(j) / (i_width -1);
            auto g = static_cast<double>(i) / (i_height -1);
            auto b = 0; 

            int ir = static_cast<int>(255 * r);
            int ig = static_cast<int>(255 * g);
            int ib = static_cast<int>(255 * b);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    } 




}
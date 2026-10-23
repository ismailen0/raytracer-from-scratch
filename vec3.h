#ifndef VEC3H
#define VEC3H

#include <cmath>
#include <iostream>

class vec3 {
    public:
        double e[3];

        vec3():e{0,0,0}{}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2} {} 

        double x() const { return e[0];}
        double y() const{ return e[1];}
        double z() const { return e[2];}

        vec3 operator-() const { return vec3(-e[0],-e[1],-e[2]);}
        double operator[](int t) const { return e[t];}
        double& operator[](int t){ return e[t];}

        vec3& operator +=(const vec3& v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *(this);
        }

        vec3& operator *=(double x){
            e[0] *= x;
            e[1] *= x; 
            e[2] *= x; 
            return *(this);
        }
        vec3& operator/=(double t) {
        return ((*this) *= (1/t));
        }
        double length() const {
        return std::sqrt(length_squared());
        }
        double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        } 
};

using point3 = vec3;
inline std::ostream& operator<<(std::ostream& o, const vec3& v){
    return o << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.e[0]+v.e[0],u.e[1]+v.e[1],u.e[2]+v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}
inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}
inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}
#endif
#include <random>

#include "vec3.h"

float rand_float() {
    static std::default_random_engine gen;
    static std::uniform_real_distribution<float> rand_real(0, 1);
    return rand_real(gen);
}
vec3 rand_in_unit_sphere() {
    vec3 p; 
    do {
        p = 2.0f * vec3(rand_float(), rand_float(), rand_float()) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0f);
    return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

#include <random>

#include "vec3.h"
#include "context.h"

float rand_float(const context& ctx) {
    return ctx.rand_real(ctx.gen);
}
vec3 rand_in_unit_sphere(const context& ctx) {
    vec3 p; 
    do {
        p = 2.0f * vec3(rand_float(ctx), rand_float(ctx), rand_float(ctx)) - vec3(1,1,1);
    } while (p.squared_length() >= 1.0f);
    return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

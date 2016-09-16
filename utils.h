#ifndef UTILS_H_
#define UTILS_H_

float rand_float();
float rand_float(const context& ctx);
vec3 rand_in_unit_sphere(const context& ctx);
vec3 rand_in_unit_disk(const context& ctx);
vec3 reflect(const vec3& v, const vec3& n);

#endif

#include "vec3.h"
#include "triangle.h"

// moller trumbore algorithm
bool triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    rec.mat_ptr = mat;

    vec3 p = cross(r.direction(), e1);
    float det = dot(e0, p);
    if (det < 0.01) return false;
    
    float inv_det = 1/det;
    vec3 t = r.origin() - v0;
    float u = dot(t, p) * inv_det;
    if (u < 0 || u > 1) return false;

    vec3 q = cross(t, e0);
    float v = dot(r.direction(), q) * inv_det;
    if (v < 0 || u + v > 1) return false;

    float temp = dot(e1, q) * inv_det;
    if (t_min < temp && temp < t_max) {
        rec.t = dot(e1, q) * inv_det;
        rec.p = r.point_at_parameter(rec.t);
        rec.normal = normal;
        return true;
    }

    return false;

    /* plane intersection
    float denom = dot(r.direction(), normal);
    if (std::abs(denom) < 0.001) {
        // ignore case where ray is in plane, because I'm not yet
        // sure what to do then & that shouldn't happen
        return false;
    }

    float numer = dot(v1 - r.origin(), normal);
    float t = numer / denom;
    if (t_min < t && t < t_max) {
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = normal;
        return true;
    }   

    return false;
    */
}

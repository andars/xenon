#ifndef CAMERA_H_
#define CAMERA_H_

#include "vec3.h"
#include "ray.h"
#include "context.h"

class camera {
public:
    camera(vec3 lookfrom, vec3 lookat, vec3 vup,
           float vfov, float aspect, float aperture_radius, float focal_dist);
    ray get_ray(float s, float t, const context& ctx) const;

    vec3 upper_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 origin;
    vec3 u, v, w;
    float aperture_radius;
    float focal_distance;
};

#endif

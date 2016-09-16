#include "camera.h"
#include "utils.h"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup,
               float vfov, float aspect, float a_radius, float focal_dist) {

    aperture_radius = a_radius; 
    focal_distance = focal_dist;

    float theta = float(vfov*M_PI/180);
    float half_height = float(tan(theta/2));
    float half_width = aspect*half_height;

    origin = lookfrom;
    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);

    upper_left_corner = origin - half_width*u + half_height*v - w;
    horizontal = 2*half_width*u;
    vertical = -2*half_height*v;
}

ray camera::get_ray(float s, float t, const context& ctx) const {
    vec3 focus_plane_pt = upper_left_corner + s*horizontal + t*vertical;
    vec3 r = normalize(focus_plane_pt - origin);
    vec3 focal_point = r*focal_distance + origin;

    vec3 delta = rand_in_unit_disk(ctx) * aperture_radius;
    vec3 offset = u * delta.x() + v * delta.y();
    vec3 dir = normalize(focal_point - (origin + offset));
    return ray(origin + offset, dir); 
}

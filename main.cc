#include <iostream>
#include <math.h>

#include "vec3.h"
#include "ray.h"

float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f*dot(oc, r.direction());
    float c = dot(oc,oc) - radius * radius;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return -1.0f;
    } else {
        // choose -b - sqrt because it is closer
        return (-b - float(sqrt(discriminant))) / (2.0f * a);
    }
}

vec3 ray_color(const ray& r) {
    vec3 center = vec3(0,0,-1);
    float t = hit_sphere(center, 0.5f, r);
    if (t > 0) {
        vec3 normal = unit_vector(r.point_at_parameter(t) - center);
        return 0.5*vec3(normal.x()+1, normal.y()+1, normal.z()+1);
    }

    vec3 unit_dir = unit_vector(r.direction());
    t = 0.5f*(unit_dir.y() + 1.0f);
    return (1.0f-t)*vec3(0.0, 0.0, 0.0) + t*vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 color = ray_color(r);
            int ir = int(255.99*color[0]);
            int ig = int(255.99*color[1]);
            int ib = int(255.99*color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}

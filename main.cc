#include <iostream>
#include <math.h>

#include "vec3.h"
#include "ray.h"
#include "entity.h"
#include "sphere.h"
#include "entity_list.h"

vec3 ray_color(const ray& r, entity* world) {
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5f*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }

    vec3 unit_dir = unit_vector(r.direction());
    float t = 0.5f*(unit_dir.y() + 1.0f);
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

    entity *list[2];
    list[1] = new sphere(vec3(0,0,-1), 0.5);
    list[0] = new sphere(vec3(0,-100.5f,-1), 100);
    entity *world = new entity_list(list, 2);

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 color = ray_color(r, world);
            int ir = int(255.99*color[0]);
            int ig = int(255.99*color[1]);
            int ib = int(255.99*color[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    delete list[0];
    delete list[1];
    delete world;
}

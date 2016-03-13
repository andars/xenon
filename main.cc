#include <iostream>
#include <cmath>

#include "vec3.h"
#include "utils.h"
#include "ray.h"
#include "entity.h"
#include "sphere.h"
#include "entity_list.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"

using std::sqrt;

vec3 ray_color(const ray& r, entity* world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.0001f, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attentuation;

        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attentuation, scattered)) {
            return attentuation*ray_color(scattered, world, depth+1);
        } else {
            return vec3(0,0,0);
        }
    }

    vec3 unit_dir = unit_vector(r.direction());
    float t = 0.5f*(unit_dir.y() + 1.0f);
    return (1.0f-t)*vec3(0.0, 0.0, 0.5) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 1000;
    int ny = 500;
    int ns = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    entity *list[4];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.3, 0.3, 0.8)));
    list[1] = new sphere(vec3(0.0,-100.5,-1.0), 100, new lambertian(vec3(0.2, 0.2, 0.2)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2)));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8,0.8,0.8)));

    entity *world = new entity_list(list, 4);
    camera cam;

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 color(0,0,0);
            for (int s=0; s < ns; s++) {
                float u = float(i + rand_float()) / float(nx);
                float v = float(j + rand_float()) / float(ny);
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, 0);
            }
            color /= float(ns);
            color = vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
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

#include <iostream>
#include <cmath>
#include <stdint.h>
#include <thread>

#include "vec3.h"
#include "context.h"
#include "utils.h"
#include "ray.h"
#include "entity.h"
#include "sphere.h"
#include "triangle.h"
#include "entity_list.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "diffuse_light.h"
#include "scenes.h"
#include "model.h"

using std::sqrt;

const int thread_count = 4;

vec3 ray_color(const ray& r, const entity* world, int depth, const context& ctx) {
    hit_record rec;
    if (world->hit(r, 0.01f, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attentuation;
        vec3 emitted = rec.mat_ptr->emitted();

        if (depth < 20 && rec.mat_ptr->scatter(r, rec, attentuation, scattered, ctx)) {
            return emitted + attentuation*ray_color(scattered, world, depth+1, ctx);
        } else {
            return emitted;
        }
    }

    // didn't hit anything, return background color
    vec3 unit_dir = unit_vector(r.direction());
    float t = 0.5f*(unit_dir.y() + 1.0f);
    //return vec3(0,0,0);
    //return vec3(0.01,0.01,0.01);
    return (1.0f-t)*vec3(0.2, 0.2, 0.2) + t*vec3(0.1, 0.4, 0.90);
}

void render(int nx, int ny, int ns, const entity* world, const camera& cam, uint8_t* pixels) {
    std::default_random_engine gen;
    std::uniform_real_distribution<float> rand_real(0,1);

    context ctx = {.gen = gen, .rand_real = rand_real};

    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            vec3 color(0,0,0);

            for (int s = 0; s < ns; s++) {
                float u = float(i + rand_float(ctx)) / float(nx);
                float v = float(j + rand_float(ctx)) / float(ny);
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, 0, ctx);
            }

            color /= float(ns);
            color = vec3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));

            uint8_t ir = uint8_t(fmin(254.99*color[0],255));
            uint8_t ig = uint8_t(fmin(254.99*color[1],255));
            uint8_t ib = uint8_t(fmin(254.99*color[2],255));

            pixels[3*nx*j + 3*i + 0] = ir;
            pixels[3*nx*j + 3*i + 1] = ig;
            pixels[3*nx*j + 3*i + 2] = ib;
        }
    }
}

int main() {
    const int nx = 600;//6000;
    const int ny = 400;//4500;
    const int ns = 150;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    //entity* world = single_triangle();
    entity* world = pi_setup();
    //(300,0,600), (0,0,100)
    //camera cam(vec3(300.0,0.0,600.0), vec3(0,0,200), vec3(0,1,0), 50, float(nx)/float(ny));
    camera cam(vec3(0,0,10), vec3(0,0,0), vec3(0,1,0), 90, float(nx)/float(ny));

    uint8_t** images = new uint8_t*[thread_count];
    for (int i = 0; i<thread_count; i++) {
        images[i] = new uint8_t[nx*ny*3];
    }

    std::thread threads[thread_count];
    for (int i = 0; i<thread_count; i++) {
        threads[i] = std::thread(render, nx, ny, ns/thread_count, world, cam, images[i]);
    }

    for (int i = 0; i<thread_count; i++) {
        threads[i].join();
    }

    uint8_t* final = new uint8_t[nx * ny * 3];

    for (int i = 0; i < ny*nx*3; i++) {
            float value = 0;
            for (int t = 0; t < thread_count; t++) {
                value += images[t][i];
            }
            final[i] = uint8_t(fmin(value/thread_count, 255));
    }

    for (int j = ny-1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            int ir = final[3*nx*j + 3*i + 0];
            int ig = final[3*nx*j + 3*i + 1];
            int ib = final[3*nx*j + 3*i + 2];
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

}

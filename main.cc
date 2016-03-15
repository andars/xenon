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
#include "entity_list.h"
#include "camera.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "diffuse_light.h"

using std::sqrt;

const int thread_count = 4;

vec3 ray_color(const ray& r, const entity* world, int depth, const context& ctx) {
    hit_record rec;
    if (world->hit(r, 0.01f, MAXFLOAT, rec)) {
        ray scattered;
        vec3 attentuation;
        vec3 emitted = rec.mat_ptr->emitted();

        if (depth < 30 && rec.mat_ptr->scatter(r, rec, attentuation, scattered, ctx)) {
            return emitted + attentuation*ray_color(scattered, world, depth+1, ctx);
        } else {
            return emitted;
        }
    }

    // didn't hit anything, return background color
    vec3 unit_dir = unit_vector(r.direction());
    float t = 0.5f*(unit_dir.y() + 1.0f);
    //return vec3(0,0,0);
    return vec3(0.01,0.01,0.01);
    //return (1.0f-t)*vec3(0.0, 0.0, 0.0) + t*vec3(0.1, 0.4, 0.90);
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
    srand(time(0));
    int nx = 300;//6000;
    int ny = 200;//4500;
    int ns = 800;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";


//    int entity_count = 23;
    int entity_count = 4;
    entity *list[entity_count];

    /*
    float theta = 0;
    for (int i = 0; i<16; i++) {
        list[i] = new sphere(vec3(110*cos(theta),110*sin(theta),5.0), 10, 
                             new lambertian(vec3(rand_float(), 2*rand_float(), rand_float())));
        theta += M_PI/8;
    }
    */
    //list[16] = new sphere(vec3(0.0,0.0,0.0), 100, new metal(vec3(0.6, 0.7, 0.6), 0));
    /*
    list[16] = new sphere(vec3(0.0,0.0,0.0), 100, new light(vec3(0.8, 0.6, 0.6)));
    list[17] = new sphere(vec3(0.0,150.0,400.0), 90, new metal(vec3(0.8, 0.3, 0.3), 0));
    list[18] = new sphere(vec3(150.0,-150.0,400.0), 90, new metal(vec3(0.2, 0.2, 0.8), 0.1));
    list[19] = new sphere(vec3(-150.0,-150.0,400.0), 90, new metal(vec3(0.3, 0.8, 0.3), 0)); 
    list[20] = new sphere(vec3(0.0,-30.0,150.0), 10, new metal(vec3(0.137, 0.369, 0.792), 0));
    list[21] = new sphere(vec3(30.0,30.0,150.0), 10, new metal(vec3(1.0, 0.424, 0.0),0));
    list[22] = new sphere(vec3(-30.0,30.0,150.0), 10, new metal(vec3(1.0, 0.812, 0.0),0.5));
    */

    list[0] = new sphere(vec3(0,5,-1), 3, new diffuse_light(vec3(3, 3, 3)));
    list[1] = new sphere(vec3(0.0,-100.5,-1.0), 100, new lambertian(vec3(0.2, 0.2, 0.6)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2),0.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8,0.8,0.8),0.01f));

    entity *world = new entity_list(list, entity_count);
    //(300,0,600), (0,0,100)
    //camera cam(vec3(300.0,0.0,600.0), vec3(0,0,200), vec3(0,1,0), 50, float(nx)/float(ny));
    camera cam(vec3(0,0,1), vec3(0,0,0), vec3(0,1,0), 50, float(nx)/float(ny));

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

    for (int i = 0; i < entity_count; i++) {
        delete list[i];
    }

    delete world;
}

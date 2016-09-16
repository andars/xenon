#include <iostream>

#include "model.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "diffuse_light.h"

using std::vector;

entity* metallic_spheres() {
    vector<entity*> list;
    float theta = 0;
    for (int i = 0; i<16; i++) {
        list.push_back(new sphere(vec3(110*cos(theta),110*sin(theta),5.0), 10, 
                       new lambertian(vec3(rand_float(), 2*rand_float(), rand_float()))));
        theta += M_PI/8;
    }

    //list[16] = new sphere(vec3(0.0,0.0,0.0), 100, new light(vec3(0.8, 0.6, 0.6)));
    list.push_back(new sphere(vec3(0.0,0.0,0.0), 100, new metal(vec3(0.6, 0.7, 0.6), 0)));
    list.push_back(new sphere(vec3(0.0,150.0,400.0), 90, new metal(vec3(0.8, 0.3, 0.3), 0)));
    list.push_back(new sphere(vec3(150.0,-150.0,400.0), 90, new metal(vec3(0.2, 0.2, 0.8), 0.01f)));
    list.push_back(new sphere(vec3(-150.0,-150.0,400.0), 90, new metal(vec3(0.3, 0.8, 0.3), 0))); 
    list.push_back(new sphere(vec3(0.0,-30.0,150.0), 10, new metal(vec3(0.137, 0.369, 0.792), 0)));
    list.push_back(new sphere(vec3(30.0,30.0,150.0), 10, new metal(vec3(1.0, 0.424, 0.0),0)));
    list.push_back(new sphere(vec3(-30.0,30.0,150.0), 10, new metal(vec3(1.0, 0.812, 0.0),0.2f)));

    entity* world = new entity_list(list);
    return world;
}

entity* two_spheres_with_light() {
    vector<entity*> list;

    list.push_back(new sphere(vec3(0,5,-1), 3, new diffuse_light(vec3(3, 3, 3))));
    list.push_back(new sphere(vec3(0.0,-100.5,-1.0), 100, new lambertian(vec3(0.2, 0.2, 0.6))));
    list.push_back(new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2),0.0)));
    list.push_back(new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8,0.8,0.8),0.01f)));

    entity *world = new entity_list(list);
    return world;
}

entity* single_triangle() {
    return new triangle(
            vec3(0,1,-1),
            vec3(1,-1,-1),
            vec3(-1,-1,-1),
            new lambertian(vec3(0.7,0.2,0.2)));
}

entity* pi_setup() {
    vector<entity*> list;
    list.push_back(new entity_list(load_stl("models/pi.stl")));
    list.push_back(new sphere(vec3(-20,30,70), 60, new diffuse_light(vec3(1,1,1))));
    list.push_back(new sphere(vec3(0,-200,10), 194, new metal(vec3(0.8,0.8,0.8),0.05)));
    list.push_back(new triangle(vec3(0,400,-10),
                                vec3(-200,-200,-10),
                                vec3(400,-200,-10),
                                new lambertian(vec3(0.9,0.9,0.9))));

    return new entity_list(list);
}

entity* projection_setup() {
    vector<entity*> list = load_stl("models/proj.stl");

    list.push_back(new sphere(vec3(0,1,0), 0.5, new diffuse_light(vec3(2,2,2))));
    list.push_back(new sphere(vec3(0,-100,0), 97, new lambertian(vec3(0.9,0.9,0.9))));

    return new entity_list(list);
}

entity* model_load(const char* filename) {
    return new entity_list(load_stl(filename));
}

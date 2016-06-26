#include "model.h"

entity* metallic_spheres() {
    int entity_count = 23;

    // i apologize for my poor memory management
    entity** list = new entity*[entity_count];
    float theta = 0;
    for (int i = 0; i<16; i++) {
        list[i] = new sphere(vec3(110*cos(theta),110*sin(theta),5.0), 10, 
                             new lambertian(vec3(rand_float(), 2*rand_float(), rand_float())));
        theta += M_PI/8;
    }

    //list[16] = new sphere(vec3(0.0,0.0,0.0), 100, new light(vec3(0.8, 0.6, 0.6)));
    list[16] = new sphere(vec3(0.0,0.0,0.0), 100, new metal(vec3(0.6, 0.7, 0.6), 0));
    list[17] = new sphere(vec3(0.0,150.0,400.0), 90, new metal(vec3(0.8, 0.3, 0.3), 0));
    list[18] = new sphere(vec3(150.0,-150.0,400.0), 90, new metal(vec3(0.2, 0.2, 0.8), 0.01f));
    list[19] = new sphere(vec3(-150.0,-150.0,400.0), 90, new metal(vec3(0.3, 0.8, 0.3), 0)); 
    list[20] = new sphere(vec3(0.0,-30.0,150.0), 10, new metal(vec3(0.137, 0.369, 0.792), 0));
    list[21] = new sphere(vec3(30.0,30.0,150.0), 10, new metal(vec3(1.0, 0.424, 0.0),0));
    list[22] = new sphere(vec3(-30.0,30.0,150.0), 10, new metal(vec3(1.0, 0.812, 0.0),0.2f));

    entity* world = new entity_list(list, entity_count);
    return world;
}

entity* two_spheres_with_light() {
    int entity_count = 4;
    entity** list = new entity*[entity_count];

    list[0] = new sphere(vec3(0,5,-1), 3, new diffuse_light(vec3(3, 3, 3)));
    list[1] = new sphere(vec3(0.0,-100.5,-1.0), 100, new lambertian(vec3(0.2, 0.2, 0.6)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2),0.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8,0.8,0.8),0.01f));

    entity *world = new entity_list(list, entity_count);
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
    model m = load_stl("pi.stl");
    int entity_count = m.count+3;
    entity** list = new entity*[entity_count];
    for (int i = 0; i<m.count; i++) {
        list[i] = m.triangles[i];
    }
    list[entity_count-3] = new sphere(vec3(-20,30,70), 60, new diffuse_light(vec3(1,1,1)));
    list[entity_count-2] = new sphere(vec3(0,-200,10), 194, new metal(vec3(0.8,0.8,0.8),0.05));
    list[entity_count-1] = new triangle(
                                    vec3(0,400,-10),
                                    vec3(-200,-200,-10),
                                    vec3(400,-200,-10),
                                    new lambertian(vec3(0.9,0.9,0.9)));

    return new entity_list(list, entity_count);
}

entity* projection_setup() {
    model m = load_stl("proj.stl");
    int entity_count = m.count + 2;
    entity** list = new entity*[entity_count];
    for (int i = 0; i<m.count; i++) {
        list[i] = m.triangles[i];
    }

    list[entity_count-2] = new sphere(vec3(0,1,0), 0.5, new diffuse_light(vec3(2,2,2)));
    list[entity_count-1] = new sphere(vec3(0,-100,0), 97, new lambertian(vec3(0.9,0.9,0.9)));

    return new entity_list(list, entity_count);
}

entity* model_load(const char* filename) {
    model m = load_stl(filename);
    int entity_count = m.count;
    entity** list = new entity*[entity_count];
    for (int i = 0; i<m.count; i++) {
        list[i] = m.triangles[i];
    }
    return new entity_list(list, entity_count);
}
#ifndef ENTITY_H_
#define ENTITY_H_

#include "vec3.h"
#include "ray.h"
#include "bbox.h"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material* mat_ptr;
};

class entity {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    virtual ~entity() {}

    material* mat;
    bbox bounds;
};

#endif

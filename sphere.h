#ifndef SPHERE_H_
#define SPHERE_H_

#include "entity.h"
#include "material.h"

class sphere: public entity {   
public:
    sphere() {}
    sphere(vec3 cen, float r, material* m): center(cen), radius(r) {
        mat = m; //meh?
        bounds = bbox(vec3(cen.x() - r, cen.y() - r, cen.z() - r),
                      vec3(cen.x() + r, cen.y() + r, cen.z() + r));
    }

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    vec3 center;
    float radius;

    ~sphere() {
        delete mat;
    }
};

#endif

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "entity.h"
#include "material.h"
#include "bbox.h"

class triangle: public entity {
public:
    triangle(const vec3& a, const vec3& b, const vec3& c, material* m)
        :v0(a), v1(b), v2(c) 
    { 
        using std::min;
        using std::max;
        e0 = v1 - v0;
        e1 = v2 - v0;
        normal = normalize(cross(e0, e1));
        bounds = bbox::U(bbox(v0, v1), v2);

        mat = m;
    }

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    // counter clockwise winding
    vec3 v0;
    vec3 v1;
    vec3 v2;

    vec3 e0;
    vec3 e1;

    vec3 normal;
};

#endif

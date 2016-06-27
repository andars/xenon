#ifndef MESH_H_
#define MESH_H_

#include <vector>

#include "entity.h"
#include "triangle.h"

class mesh: public entity {
public:
    mesh(triangle** tris, int c, material* m) {
        triangles.assign(tris, tris + c);
        mat = m;
    }

    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    std::vector<triangle*> triangles;
};

#endif

#ifndef BBOX_H_
#define BBOX_H_

#include "vec3.h"
#include "ray.h"

using std::min;
using std::max;

class bbox {
public:
    bbox() {
        float inf = std::numeric_limits<float>::infinity();
        minp = vec3(inf, inf, inf);
        maxp = vec3(-inf, -inf, -inf);
    }

    bbox(const vec3& p1, const vec3& p2) {
        minp = vec3(min(p1.x(), p2.x()), min(p1.y(), p2.y()), min(p1.z(), p2.z()));
        maxp = vec3(max(p1.x(), p2.x()), max(p1.y(), p2.y()), max(p1.z(), p2.z()));
    }

    bool intersects(const ray& r, float t_min, float t_max) const;

    static bbox U(const bbox& box, const vec3& p) {
        bbox ret = box;
        ret.minp[0] = min(box.minp[0], p[0]);
        ret.minp[1] = min(box.minp[1], p[1]);
        ret.minp[2] = min(box.minp[2], p[2]);
        ret.maxp[0] = max(box.maxp[0], p[0]);
        ret.maxp[1] = max(box.maxp[1], p[1]);
        ret.maxp[2] = max(box.maxp[2], p[2]);
        return ret;
    }

    static bbox U(const bbox& b1, const bbox& b2) {
        bbox ret = b1;
        ret.minp[0] = min(b1.minp[0], b2.minp[0]);
        ret.minp[1] = min(b1.minp[1], b2.minp[1]);
        ret.minp[2] = min(b1.minp[2], b2.minp[2]);
        ret.maxp[0] = max(b1.maxp[0], b2.maxp[0]);
        ret.maxp[1] = max(b1.maxp[1], b2.maxp[1]);
        ret.maxp[2] = max(b1.maxp[2], b2.maxp[2]);
        return ret;
    }

    vec3 minp;
    vec3 maxp;
};

#endif

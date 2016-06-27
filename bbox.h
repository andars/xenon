#ifndef BBOX_H_
#define BBOX_H_

#include "vec3.h"
#include "ray.h"

class bbox {
public:
    bbox() {
        float inf = std::numeric_limits<float>::infinity();
        minp = vec3(inf, inf, inf);
        maxp = vec3(-inf, -inf, -inf);
    }

    bbox(const vec3& p1, const vec3& p2) {
        using std::min;
        using std::max;
        minp = vec3(min(p1.x(), p2.x()), min(p1.y(), p2.y()), min(p1.z(), p2.z()));
        maxp = vec3(max(p1.x(), p2.x()), max(p1.y(), p2.y()), max(p1.z(), p2.z()));
    }

    bool intersects(const ray& r, float t_min, float t_max) const {
        for (int i = 0; i < 3; i++) {
            float inv = 1.f / r.direction()[i];
            vec3 o = r.origin();
            float t_near = (minp[i] - o[i]) * inv;
            float t_far = (maxp[i] - o[i]) * inv;

            if (t_near > t_far) {
                float t = t_near;
                t_near = t_far;
                t_far = t;
            }

            t_min = t_near > t_min ? t_near : t_min;
            t_max = t_far < t_max ? t_far : t_max;
            if (t_min > t_max) return false;
        }
        return true;
    }

    static bbox U(const bbox& box, const vec3& p) {
        using std::min;
        using std::max;

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
        using std::min;
        using std::max;

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

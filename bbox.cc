#include "bbox.h"

bool bbox::intersects(const ray& r, float t_min, float t_max) const {
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

#ifndef ENTITY_H_
#define ENTITY_H_

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class entity {
public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
    virtual ~entity() {}
};

#endif

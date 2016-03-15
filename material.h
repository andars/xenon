#ifndef MATERIAL_H_
#define MATERIAL_H_

class material {
public:
    virtual ~material() {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attentuation,
                         ray& scattered) const = 0;
    virtual vec3 emitted() const {
        return vec3(0,0,0);
    }
};

#endif

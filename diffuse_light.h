#ifndef DIFFUSE_LIGHT_H_
#define DIFFUSE_LIGHT_H_

class diffuse_light: public material {
public:
    diffuse_light(const vec3& e): emit(e) {}
    
    virtual bool scatter(const ray&, const hit_record&,
                        vec3&, ray&) const {
        return false;
    }

    virtual vec3 emitted() const {
        return emit;
    }

    vec3 emit;
};
#endif

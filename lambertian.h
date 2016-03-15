#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

class lambertian: public material {
public:
    lambertian(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray&, const hit_record& rec, vec3& attentuation, 
                         ray& scattered, const context& ctx) const {
        vec3 target = rec.p + rec.normal + rand_in_unit_sphere(ctx);
        scattered = ray(rec.p, target-rec.p);
        attentuation = albedo;
        return true;
    }

    vec3 albedo;
};

#endif

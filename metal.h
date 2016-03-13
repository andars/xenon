#ifndef METAL_H_
#define METAL_H_

class metal: public material {
public:
    metal(const vec3& a): albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         vec3& attentuation, ray& scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attentuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    vec3 albedo;
};

#endif

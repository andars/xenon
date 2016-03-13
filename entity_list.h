#ifndef ENTITY_LIST_H_
#define ENTITY_LIST_H_

class entity_list: public entity {
public:
    entity_list() {}
    entity_list(entity** l, int n): list(l), list_size(n) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    entity** list;
    int list_size;
};

bool entity_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record tmp_rec;
    bool any_hit = false;
    float closest = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest, tmp_rec)) {
            any_hit = true;
            closest = tmp_rec.t;
            rec = tmp_rec;
        }
    }
    return any_hit;
}


#endif

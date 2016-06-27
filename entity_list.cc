#include "entity_list.h"

bool entity_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    //if (!bounds.intersects(r, t_min, t_max)) return false;

    hit_record tmp_rec;
    bool any_hit = false;
    float closest = t_max;
    for (entity* e : list) {
        if (e->hit(r, t_min, closest, tmp_rec)) {
            any_hit = true;
            closest = tmp_rec.t;
            rec = tmp_rec;
        }
    }
    return any_hit;
}

void entity_list::compute_bbox() {
    using std::min;
    using std::max;

    for (entity* e : list) {
        bounds = bbox::U(bounds, e->bounds);
    }

}

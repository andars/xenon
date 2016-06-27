#ifndef ENTITY_LIST_H_
#define ENTITY_LIST_H_

#include <vector>

#include "entity.h"

class entity_list: public entity {
public:
    entity_list() {}
    entity_list(std::vector<entity*> l): list(std::move(l)) {
        compute_bbox(); 
    }
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

private:
    void compute_bbox();
    std::vector<entity*> list;
};



#endif

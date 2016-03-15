#ifndef ENTITY_LIST_H_
#define ENTITY_LIST_H_

#include "entity.h"

class entity_list: public entity {
public:
    entity_list() {}
    entity_list(entity** l, int n): list(l), list_size(n) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

    entity** list;
    int list_size;
};



#endif

#ifndef MODEL_H_
#define MODEL_H_

#include "entity.h"

struct model {
    entity** triangles;
    int count;
};

model load_stl(const char* filename);

#endif

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "entity.h"
#include "triangle.h"
#include "lambertian.h"
#include "metal.h"
#include "model.h"

std::vector<entity*> load_stl(const char* filename) {
    FILE* stl = fopen(filename, "rb");

    if (!stl) {
        std::cerr << "failed to open " << filename << "\n";
    }

    uint8_t header[80];
    fread(header, sizeof(header), 1, stl);
    
    uint32_t tri_count;
    fread(&tri_count, 1, 4, stl); 

    std::vector<entity*> triangles;
    
    for (int i = 0; i < tri_count; i++) {
        float n[3];
        float v0[3];
        float v1[3];
        float v2[3];
        fread(n, 3, 4, stl);
        fread(v0, 3, 4, stl);
        fread(v1, 3, 4, stl);
        fread(v2, 3, 4, stl);

        uint16_t attr_bytes;
        fread(&attr_bytes, 2, 1, stl);
        vec3 normal(n[0],n[1],n[2]);
        vec3 vec0(v0[0],v0[1],v0[2]);
        vec3 vec1(v1[0],v1[1],v1[2]);
        vec3 vec2(v2[0],v2[1],v2[2]);

        if (normal.length() > 0) {
            //switch winding order if normal is given & differs from computed
            vec3 computed = unit_vector(cross(vec1-vec0, vec2-vec0));
            if ((unit_vector(normal) - computed).length() > 0.01) {
                vec3 temp = vec1;
                vec1 = vec2;
                vec2 = temp;
            }
        }
        triangles.push_back(new triangle(vec0, vec1, vec2,
                            new metal(vec3(0.988,0.05,0.05),0.1)));
    }
    fclose(stl);

    return triangles;
}

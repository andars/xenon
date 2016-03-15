#include <stdint.h>
#include <stdio.h>

#include "entity.h"
#include "triangle.h"
#include "lambertian.h"
#include "model.h"

model load_stl(const char* filename) {
    FILE* stl = fopen(filename, "rb");

    model m;

    uint8_t header[80];
    fread(header, sizeof(header), 1, stl);
    
    uint32_t tri_count;
    fread(&tri_count, 1, 4, stl); 

    entity** triangles = new entity*[tri_count];
    
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

        triangles[i] = new triangle(
                vec3(v0[0],v0[1],v0[2]),
                vec3(v1[0],v1[1],v1[2]),
                vec3(v2[0],v2[1],v2[2]),
                new lambertian(vec3(0.2,0.2,0.9)));
    }
    fclose(stl);

    m.triangles = triangles;
    m.count = tri_count;
    return m;
}

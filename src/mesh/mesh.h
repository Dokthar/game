#include "globject.h"

#ifndef MESH_H
#define MESH_H

struct Mesh
{
    float* vertices;
    float* normals;
    float* texCoords;
    unsigned int* indices;
    unsigned int numVertices, numNormals, numTexCoords, numIndices;
    struct GLObject glObject;
};

void mesh_load(struct Mesh* mesh);
void mesh_unload(struct Mesh* mesh);
void mesh_free(struct Mesh*);

#endif

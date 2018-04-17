#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "mesh/mesh.h"
#include "material/material.h"

struct Geometry {
    struct Mesh* mesh;
    struct Material* material;
};

#endif

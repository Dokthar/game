#include <GL/glew.h>
#include "linear_algebra.h"
#include "camera.h"
#include "globject.h"
#include "material/material.h"
#include "mesh/mesh.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Geometry {
    struct Mesh *mesh;
    struct Material *material;
};

void geometry_render(const struct Geometry* geometry, const struct Camera* camera, Mat4 model);

#endif

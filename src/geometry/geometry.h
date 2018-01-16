#include <GL/glew.h>
#include "linear_algebra.h"
#include "camera.h"
#include "globject.h"
#include "material/material.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Geometry {
    struct GLObject glObject;
    struct Material *material;
};

void geometry_render(const struct Geometry* geometry, const struct Camera* camera, Mat4 model);

#endif

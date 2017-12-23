#include <GL/glew.h>
#include "linear_algebra.h"
#include "camera.h"
#include "globject.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Geometry {
    Mat4 model;
    GLuint shader;
    struct GLObject glObject;
    void (*render)(const struct Geometry*);
    void *priv_data;
};

void geometry_render(const struct Geometry* geometry, const struct Camera* camera);

#endif

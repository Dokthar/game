#include <GL/glew.h>
#include "math/linear_algebra.h"
#include "mesh/globject.h"
#include "render/camera.h"
#include "light/light.h"

#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Geometry {
    struct GLObject glObject;
    GLuint shader;
    GLuint mode;
    void (*prerender)(const struct Geometry*, const struct Camera*, const struct Lights*);
    void (*postrender)(const struct Geometry*, const struct Camera*, const struct Lights*);
    void* material;
};

void geometry_render(const struct Geometry* geometry, const struct Camera* camera, const struct Lights* lights, Mat4 model, Mat3 inverseNormal);

#endif

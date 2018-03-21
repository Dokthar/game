#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "camera.h"
#include "light/light.h"

struct Material {
    GLuint shader;
    GLuint mode;
    void (*prerender)(const struct Material*, const struct Camera*, const struct Lights*);
    void (*postrender)(const struct Material*, const struct Camera*, const struct Lights*);
};

#endif

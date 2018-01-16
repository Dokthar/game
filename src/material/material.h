#include <GL/glew.h>
#include "camera.h"

#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    GLuint shader;
    GLuint mode;
    void (*prerender)(const struct Material*, const struct Camera*);
    void (*postrender)(const struct Material*, const struct Camera*);
};

#endif

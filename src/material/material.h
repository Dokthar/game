#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "camera.h"
#include "light/light.h"
#include "matparam.h"

struct Material {
    const char* name;
    GLuint shader;
    GLuint mode;
    void (*prerender)(const struct Material*, const struct Camera*, const struct Lights*);
    void (*postrender)(const struct Material*, const struct Camera*, const struct Lights*);
    unsigned int nb_params;
    struct Matparam* params;
};

void material_init(struct Material* mat, const char* name, unsigned int nb_params, struct Matparam *params);

void material_prerender(const struct Material*, const struct Camera*, const struct Lights*);

void material_postrender(const struct Material*, const struct Camera*, const struct Lights*);

#endif

#include "material.h"

#ifndef SOLID_TEXTURE_H
#define SOLID_TEXTURE_H

struct SolidTextureMaterial {
    struct Material material;
    GLuint texture;
};

void solid_texture_material(struct SolidTextureMaterial* dest, GLuint texture);

void solid_texture_shader_free(void);

#endif

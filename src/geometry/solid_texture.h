#include "material/material.h"
#include "texture.h"

#ifndef SOLID_TEXTURE_H
#define SOLID_TEXTURE_H

struct SolidTextureMaterial {
    struct Material mat;
    GLuint texture;
};

void solid_texture_material_init(struct SolidTextureMaterial* material);

#endif

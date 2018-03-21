#include "material/material.h"
#include "light/phong.h"

#ifndef PHONG_TEXTURE_H
#define PHONG_TEXTURE_H

struct PhongTextureMaterial {
    struct Material mat;
    GLuint texture;
    struct PhongMaterial phong;
};

void phong_texture_material_init(struct PhongTextureMaterial* material);

#endif

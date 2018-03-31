#include "material/material.h"
#include "light/phong.h"

#ifndef PHONG_TEXTURE_H
#define PHONG_TEXTURE_H

struct PhongTextureMaterial {
    struct Material mat;
    struct Matparam ambient;
    struct Matparam diffuse;
    struct Matparam specular;
    struct Matparam shininess;
    struct Matparam texture;
};

void phong_texture_material_init(struct PhongTextureMaterial* material);

#endif

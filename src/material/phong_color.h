#include "material/material.h"
#include "light/phong.h"

#ifndef PHONG_COLOR_H
#define PHONG_COLOR_H

struct PhongColorMaterial {
    struct Material mat;
    struct Matparam ambient;
    struct Matparam diffuse;
    struct Matparam specular;
    struct Matparam shininess;
    struct Matparam color;
};

void phong_color_material_init(struct PhongColorMaterial* material);

#endif

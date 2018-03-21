#include "material/material.h"
#include "light/phong.h"

#ifndef PHONG_COLOR_H
#define PHONG_COLOR_H

struct PhongColorMaterial {
    struct Material mat;
    Vec3 color;
    struct PhongMaterial phong;
};

void phong_color_material_init(struct PhongColorMaterial* material);

#endif

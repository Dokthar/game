#include "material/material.h"

#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

struct SolidColorMaterial {
    struct Material mat;
    Vec3 color;
};

void solid_color_material_init(struct SolidColorMaterial* material);

void solid_color_material_set_color(struct SolidColorMaterial* mat, float r, float g, float b);

void solid_color_load_uniform(const struct Material* material, const float* color);

#endif

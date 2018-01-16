#include "material.h"

#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

struct SolidColorMaterial {
    struct Material material;
    Vec3 color;
};

void solid_color_material(struct SolidColorMaterial* dest, float r, float g, float b);

void solid_color_shader_free(void);

#endif

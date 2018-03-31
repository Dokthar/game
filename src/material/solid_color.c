#include "solid_color.h"
#include "shaders.h"

void solid_color_load_uniform(const struct Material* mat, const float* color) {
    glUniform3fv(glGetUniformLocation(mat->shader, "solidColor"), 1, color);
}

void solid_color_material_init(struct SolidColorMaterial* solidcolor) {
    struct Material* mat = &solidcolor->mat;

    material_init(mat, "solid color", 1, &solidcolor->color);
    mat->shader = game_shaders[SHADER_SOLID_COLOR];

    solidcolor->color.type = RGB;
    solidcolor->color.name = "solidColor";
    solid_color_material_set_color(solidcolor, 0, 0, 0);
}

void solid_color_material_set_color(struct SolidColorMaterial* mat, float r, float v, float b) {
    matparam_set_color_rgb(&mat->color, r, v, b);
}

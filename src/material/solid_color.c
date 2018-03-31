#include "solid_color.h"
#include "shaders.h"

void solid_color_load_uniform(const struct Material* mat, const float* color) {
    glUniform3fv(glGetUniformLocation(mat->shader, "solidColor"), 1, color);
}

void solid_color_material_init(struct SolidColorMaterial* solidcolor) {
    struct Material* mat = &solidcolor->mat;

    material_init(mat, "solid color", 1, &solidcolor->color);
    mat->shader = game_shaders[SHADER_SOLID_COLOR];

    solidcolor->color.type = VEC3;
    solidcolor->color.name = "solidColor";
    solid_color_material_set_color(solidcolor, 0, 0, 0);
}

void solid_color_material_set_color(struct SolidColorMaterial* mat, float r, float g, float b) {
    mat->color.value._vec3[0] = r;
    mat->color.value._vec3[1] = g;
    mat->color.value._vec3[2] = b;
}

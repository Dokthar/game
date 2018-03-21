#include "solid_color.h"
#include "shaders.h"

void solid_color_load_uniform(const struct Material* mat, const float* color) {
    glUniform3fv(glGetUniformLocation(mat->shader, "solidColor"), 1, color);
}

static void solid_color_prerender(const struct Material* mat, const struct Camera* camera, const struct Lights* lights) {
    solid_color_load_uniform(mat, ((const struct SolidColorMaterial*)mat)->color);
}

void solid_color_material_init(struct SolidColorMaterial* mat) {
    struct Material* dest = (struct Material*) mat;

    dest->shader = game_shaders[SHADER_SOLID_COLOR];
    dest->mode = GL_FILL;
    dest->prerender = solid_color_prerender;
    dest->postrender = NULL;
}

void solid_color_material_set_color(struct SolidColorMaterial* mat, float r, float g, float b) {
    mat->color[0] = r;
    mat->color[1] = g;
    mat->color[2] = b;
}

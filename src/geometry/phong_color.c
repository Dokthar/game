#include "solid_color.h"
#include "phong_color.h"
#include "shaders.h"

static void phong_color_prerender(const struct Material* mat, const struct Camera* camera, const struct Lights* lights) {
    solid_color_load_uniform(mat, ((const struct PhongColorMaterial*)mat)->color);
    light_load_uniforms(mat->shader, lights->directional, lights->numDirectional, lights->local, lights->numLocal);
    phong_load_material_uniform(mat->shader, &((const struct PhongColorMaterial*)mat)->phong);
}

void phong_color_material_init(struct PhongColorMaterial* mat) {
    struct Material* dest = (struct Material*) mat;

    dest->shader = game_shaders[SHADER_PHONG_COLOR];
    dest->mode = GL_FILL;
    dest->prerender = phong_color_prerender;
    dest->postrender = NULL;
}

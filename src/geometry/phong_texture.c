#include "phong_texture.h"
#include "shaders.h"

static void phong_texture_prerender(const struct Material* mat, const struct Camera* camera, const struct Lights* lights) {
    glBindTexture(GL_TEXTURE_2D, ((const struct PhongTextureMaterial*)mat)->texture);
    light_load_uniforms(mat->shader, lights->directional, lights->numDirectional, lights->local, lights->numLocal);
    phong_load_material_uniform(mat->shader, &((const struct PhongTextureMaterial*)mat)->phong);
}

static void phong_texture_postrender(const struct Material* mat, const struct Camera* camera, const struct Lights* lights) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void phong_texture_material_init(struct PhongTextureMaterial* mat) {
    struct Material* dest = (struct Material*) mat;

    dest->shader = game_shaders[SHADER_PHONG_TEXTURE];
    dest->mode = GL_FILL;
    dest->prerender = phong_texture_prerender;
    dest->postrender = phong_texture_postrender;
}

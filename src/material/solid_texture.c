#include "solid_texture.h"
#include "shaders.h"

static void solid_texture_prerender(const struct Material* mat, const struct Camera* camera, const struct Lights* lights) {
    glBindTexture(GL_TEXTURE_2D, ((const struct SolidTextureMaterial*)mat)->texture);
}

static void solid_texture_postrender(const struct Material* mat, const struct Camera* camera, const struct Lights* lights) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void solid_texture_material_init(struct SolidTextureMaterial* mat) {
    struct Material* dest = (struct Material*) mat;

    dest->shader = game_shaders[SHADER_SOLID_TEXTURE];
    dest->mode = GL_FILL;
    dest->prerender = solid_texture_prerender;
    dest->postrender = solid_texture_postrender;
}

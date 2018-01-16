#include "solid_texture.h"
#include "shader.h"

static GLuint shader = 0;

static void solid_texture_prerender(const struct Material* material, const struct Camera* camera) {
    glBindTexture(GL_TEXTURE_2D, ((const struct SolidTextureMaterial*)material)->texture);
}

static void solid_texture_postrender(const struct Material* material, const struct Camera* camera) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void solid_texture_material(struct SolidTextureMaterial* dest, GLuint texture) {
    if (!shader) {
        shader = shader_compile("shaders/solid_texture.vert", "shaders/solid_texture.frag");
    }
    dest->material.shader = shader;
    dest->material.mode = GL_FILL;
    dest->material.prerender = solid_texture_prerender;
    dest->material.postrender = solid_texture_postrender;
    dest->texture = texture;
}

void solid_texture_shader_free(void) {
    glDeleteProgram(shader);
}

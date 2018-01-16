#include "solid_color.h"
#include "shader.h"

static GLuint shader = 0;

static void load_solid_color_uniforms(const struct Material* material, const struct Camera* camera) {
    glUniform3fv(glGetUniformLocation(material->shader, "solidColor"), 1, (float*)((const struct SolidColorMaterial*)material)->color);
}

void solid_color_material(struct SolidColorMaterial* dest, float r, float g, float b) {
    if (!shader) {
        shader = shader_compile("shaders/solid_color.vert", "shaders/solid_color.frag");
    }
    dest->material.shader = shader;
    dest->material.mode = GL_FILL;
    dest->material.prerender = load_solid_color_uniforms;
    dest->material.postrender = 0;
    dest->color[0] = r;
    dest->color[1] = g;
    dest->color[2] = b;
}

void solid_color_shader_free(void) {
    glDeleteProgram(shader);
}

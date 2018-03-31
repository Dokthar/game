#include "material.h"
#include <stdlib.h>
#include <stdio.h>

void material_init(struct Material* mat, const char* name, unsigned int nb_params, struct Matparam *params) {
    mat->name = name;
    mat->shader = 0;
    mat->prerender = material_prerender;
    mat->postrender = material_postrender;
    mat->mode = GL_FILL;
    mat->nb_params = nb_params;
    mat->params = params;
}

void material_prerender(const struct Material *mat, const struct Camera *cam, const struct Lights *lights) {
    unsigned int i;
    struct Matparam param;
    GLint location;

    for (i = 0; i < mat->nb_params; i++) {
        param = mat->params[i];
        location = glGetUniformLocation(mat->shader, param.name);
        switch (param.type) {
        case INT:
            glUniform1i(location, param.value._int);
            break;
        case FLOAT:
            glUniform1f(location, param.value._float);
            break;
        case VEC2:
            glUniform2fv(location, 1, param.value._vec2);
            break;
        case VEC3:
            glUniform3fv(location, 1, param.value._vec3);
            break;
        case VEC4:
            glUniform4fv(location, 1, param.value._vec4);
            break;
        case TEXTURE:
            glBindTexture(GL_TEXTURE_2D, param.value._texture);
            break;
        }
    }
}

void material_postrender(const struct Material *mat, const struct Camera *cam, const struct Lights *lights) {
}

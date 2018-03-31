#include "matparam.h"

void matparam_set_color_rgb(struct Matparam* param, float r, float g, float b) {
    param->value._vec3[0] = r;
    param->value._vec3[1] = g;
    param->value._vec3[2] = b;
}

void matparam_set_texture(struct Matparam* param, GLuint texture) {
    param->value._texture = texture;
}

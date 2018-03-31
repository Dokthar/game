#include "matparam.h"

void matparam_set_int(struct Matparam* param, int i) {
    param->value._int = i;
}

void matparam_set_float(struct Matparam* param, float f) {
    param->value._float = f;
}

void matparam_set_color_vec3(struct Matparam* param, Vec3 rgb) {
    param->value._vec3[0] = rgb[0];
    param->value._vec3[1] = rgb[1];
    param->value._vec3[2] = rgb[2];
}

void matparam_set_color_rgb(struct Matparam* param, float r, float g, float b) {
    param->value._vec3[0] = r;
    param->value._vec3[1] = g;
    param->value._vec3[2] = b;
}

void matparam_set_texture(struct Matparam* param, GLuint texture) {
    param->value._texture = texture;
}

#include "material.h"
#include <string.h>
#include <stdio.h>

void material_init(struct Material* mat, const char* name, unsigned int nb_params, struct Matparam *params) {
    mat->name = name;
    mat->shader = 0;
    mat->mode = GL_FILL;
    mat->nb_params = nb_params;
    mat->params = params;
}

struct Matparam* material_get_param(struct Material* mat, const char* name) {
    unsigned int i;
    struct Matparam* param;

    for (i = 0; i < mat->nb_params; i++) {
        param = &mat->params[i];
	if (strcmp(name, param->name) == 0) {
	    return param;
	}
    }
    return NULL;
}


void material_set_int(struct Material* mat, const char* name, int i) {
    struct Matparam* param;

    param = material_get_param(mat, name);
    if (param) {
	param->type = INT;
	matparam_set_int(param, i);
    }
}

void material_set_float(struct Material* mat, const char* name, float f) {
    struct Matparam* param;

    param = material_get_param(mat, name);
    if (param) {
	param->type = FLOAT;
	matparam_set_float(param, f);
    }
}

void material_set_color_vec3(struct Material* mat, const char* name, Vec3 rgb) {
    struct Matparam* param;

    param = material_get_param(mat, name);
    if (param) {
	param->type = RGB;
	matparam_set_color_vec3(param, rgb);
    }
}

void material_set_color(struct Material* mat, const char* name, float r, float g, float b) {
    struct Matparam* param;

    param = material_get_param(mat, name);
    if (param) {
	param->type = RGB;
	matparam_set_color_rgb(param, r, g, b);
    }
}

void material_set_texture(struct Material* mat, const char* name, GLuint texture) {
    struct Matparam* param;

    param = material_get_param(mat, name);
    if (param) {
	param->type = TEXTURE;
	matparam_set_texture(param, texture);
    }
}

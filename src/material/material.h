#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "camera.h"
#include "light/light.h"
#include "matparam.h"

struct Material {
    const char* name;
    GLuint shader;
    GLuint mode;
    unsigned int nb_params;
    struct Matparam* params;
};

void material_init(struct Material* mat, const char* name, unsigned int nb_params, struct Matparam *params);

void material_prerender(const struct Material*, const struct Camera*, const struct Lights*);

void material_postrender(const struct Material*, const struct Camera*, const struct Lights*);

struct Matparam* material_get_param(struct Material* mat, const char* name);

void material_set_int(struct Material* mat, const char* name, int i);

void material_set_float(struct Material* mat, const char* name, float f);

void material_set_color_vec3(struct Material* mat, const char* name, Vec3 rgb);

void material_set_color(struct Material* mat, const char* name, float r, float g, float b);

void material_set_texture(struct Material* mat, const char* name, GLuint texture);

#endif

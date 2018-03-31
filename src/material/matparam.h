#ifndef MATPARAM_H
#define MATPARAM_H
#include "linear_algebra.h"
#include <GL/gl.h>

enum MatparamType {
    INT,
    FLOAT,
    VEC2,
    VEC3,
    RGB = VEC3,
    VEC4,
    RGBA = VEC4,
    TEXTURE
};

struct Matparam {
    enum MatparamType type;
    const char *name;
    union {
        int _int;
        float _float;
        Vec2 _vec2;
        Vec3 _vec3;
        Vec4 _vec4;
        GLuint _texture;
    } value;
};

void matparam_set_int(struct Matparam* param, int i);

void matparam_set_float(struct Matparam* param, float f);

void matparam_set_color_vec3(struct Matparam* param, Vec3 rgb);

void matparam_set_color_rgb(struct Matparam* param, float r, float g, float b);

void matparam_set_texture(struct Matparam* param, GLuint texture);

#endif

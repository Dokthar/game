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

#endif

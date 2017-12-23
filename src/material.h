#ifndef MATERIAL_H
#define MATERIAL_H

#include "linear_algebra.h"
#include "shader.h"

struct Material {
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    float shininess;
    GLuint shader;
};

#endif

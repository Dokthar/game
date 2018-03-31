#include "light.h"

#ifndef PHONG_H
#define PHONG_H

struct PhongMaterial {
    Vec3 ambient;
    Vec3 diffuse;
    Vec3 specular;
    float shininess;
};

#endif

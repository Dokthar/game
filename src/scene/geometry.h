#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "gl/globject.h"
#include "material/material.h"

struct Geometry {
    struct GLObject glObject;
    struct Material* material;
};

#endif

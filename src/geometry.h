#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "mesh.h"
#include "material.h"
#include "globject.h"
#include "linear_algebra.h"

struct Geometry
{
	struct GLObject *globject;
	struct Mesh *mesh;
	struct Material *material;
	Mat4 *transform;
};

#endif

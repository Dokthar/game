#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "geometry/geometry.h"
#include "node.h"

int render_graph(struct Node* root, const struct Camera* cam, const struct Lights* lights);

void render_geometry(const struct Geometry* geometry, const struct Camera* camera, const struct Lights* lights, Mat4 model, Mat3 inverseNormal);

#endif

#ifndef RENDERER_H
#define RENDERER_H

#include "scene/geometry.h"
#include "scene/node.h"

int render_graph(struct Node* root, const struct Camera* cam, const struct Lights* lights);

void render_geometry(const struct Geometry* geometry, const struct Camera* camera, const struct Lights* lights, Mat4 model, Mat3 inverseNormal);

#endif

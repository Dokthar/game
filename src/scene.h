#include "light/light.h"
#include "node.h"
#include "viewer.h"

#ifndef SCENE_H
#define SCENE_H

struct Scene {
    struct Lights lights;
    struct Node root;
};

void scene_init(struct Scene* scene);
#define scene_free(scene) graph_free(&(scene)->root)

#define scene_add(scene, node) node_add_child(&(scene)->root, (node))

int scene_render(struct Scene* scene, struct Viewer* viewer);

#endif

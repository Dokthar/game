#ifndef SCENE_H
#define SCENE_H

#include "light/light.h"
#include "node.h"

struct Scene {
    struct Lights lights;
    struct Node root;
};

void scene_init(struct Scene* scene);
#define scene_free(scene) graph_free(&(scene)->root)

#define scene_add(scene, node) node_add_child(&(scene)->root, (node))

#endif

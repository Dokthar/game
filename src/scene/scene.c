#include "scene.h"
#include "render/renderer.h"

void scene_init(struct Scene* scene) {
    scene->lights.numDirectional = 0;
    scene->lights.numLocal = 0;
    node_init(&scene->root, NULL);
}

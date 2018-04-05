#include "scene.h"
#include "render/renderer.h"

void scene_init(struct Scene* scene) {
    scene->lights.numDirectional = 0;
    scene->lights.numLocal = 0;
    node_init(&scene->root, NULL);
}

int scene_render(struct Scene* scene, struct Viewer* viewer) {
    return render_graph(&scene->root, &viewer->camera, &scene->lights);
}

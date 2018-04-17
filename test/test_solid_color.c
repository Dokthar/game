#include <stdio.h>
#include <stdlib.h>
#include "viewer.h"
#include "scene/scene.h"
#include "asset_manager.h"
#include "gl/globject.h"
#include "mesh/box.h"
#include "material/solid_color.h"

int main(int argc, char** argv) {
    struct Viewer* viewer = NULL;
    struct Scene scene;
    struct Mesh cube = {0};
    struct SolidColorMaterial solidcolor = {0};
    struct Geometry geom = {0};
    double size;
    int ret = 1;

    asset_manager_add_path(".");
    asset_manager_add_path("..");

    if (argc != 3) {
        fprintf(stderr, "Usage: %s size out.png\n", argv[0]);
    } else if (!(size = strtod(argv[1], NULL))) {
        fprintf(stderr, "Error: bad size\n");
    } else if (!(viewer = viewer_new(640, 480, __FILE__))) {
        fprintf(stderr, "Error: cannot start viewer\n");
    } else if (!make_box(&cube, size, size, size)) {
        fprintf(stderr, "Error: failed to create cube\n");
    } else {
        solid_color_material_init(&solidcolor);
        solid_color_material_set_color(&solidcolor, 1.0, 0.0, 1.0);
        geom.mesh = &cube;
        geom.material = &solidcolor.mat;

        scene_init(&scene);
        viewer->viewport.scene = &scene;
        scene.root.geometry = &geom;

        viewer_next_frame(viewer);
        viewer_render(viewer);

        if (viewer_screenshot(viewer, argv[2])) {
            ret = 0;
        } else {
            fprintf(stderr, "Error: failed to take screenshot\n");
        }
        scene_free(&scene);
    }

    renderer_free_mesh(viewer->context.renderer, &cube);
    mesh_free(&cube);
    viewer_free(viewer);

    return ret;
}

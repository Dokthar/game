#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

#include "viewer.h"
#include "render/camera.h"
#include "gl/globject.h"
#include "texture.h"
#include "scene/scene.h"
#include "asset_manager.h"
#include "material/solid_color.h"
#include "material/solid_texture.h"
#include "material/phong_color.h"
#include "material/phong_texture.h"
#include "mesh/obj.h"
#include "mesh/box.h"
#include "mesh/icosphere.h"
#include "test/util/scenes_basic.h"
#include "test/util/color.h"
#include "test/util/light.h"
#include "test/util/callbacks.h"

int main() {
    struct Viewer *viewer, *viewer2;
    double t = 0.0, dt;
    struct Mesh cubeMesh = {0};
    struct Geometry cube2 = {0};
    struct Scene scene, scene2;
    struct Node nodeCube;
    Vec3 color = {0};
    struct PhongColorMaterial sphereMat;
    struct PhongTextureMaterial textureMat;
    struct SolidTextureMaterial solidTex;

    asset_manager_add_path(".");
    asset_manager_add_path("./test/assets");
    asset_manager_add_path("..");
    asset_manager_add_path("../test/assets");
    viewer = viewer_new(640, 480, "Game");
    viewer->context.cursor_callback = cursor_rotate_scene;
    viewer->context.wheel_callback = wheel_callback;
    viewer->context.key_callback = key_callback;
    viewer->context.close_callback = close_callback;
    viewer2 = viewer_new(640, 480, "Game 2");
    viewer2->context.cursor_callback = cursor_rotate_scene;
    viewer2->context.wheel_callback = wheel_callback;
    viewer2->context.key_callback = key_callback;
    viewer2->context.close_callback = close_callback;
    running = 1;

    viewer_make_current(viewer);
    phong_color_material_init(&sphereMat);
    phong_texture_material_init(&textureMat);
    material_set_texture(&textureMat.mat, "tex", asset_manager_load_texture("png/rgb_tux.png"));

    viewer_make_current(viewer2);
    solid_texture_material_init(&solidTex);
    matparam_set_texture(&(solidTex.texture), asset_manager_load_texture("png/rgb_tux.png"));
    cube2.material = &solidTex.mat;
    cube2.mesh = &cubeMesh;
    make_box(&cubeMesh, 2.0, 2.0, 2.0);
    renderer_load_mesh(viewer2->context.renderer, &cubeMesh);
    mesh_free(&cubeMesh);

    viewer_make_current(viewer);
    scene_init(&scene);
    viewer->viewport.scene = &scene;

    spheres_and_boxes(&sphereMat.mat, &textureMat.mat, &scene.root);

    test_init_local_light(&scene.lights.local[0]);
    scene.lights.numLocal = 1;

    viewer_make_current(viewer2);
    scene_init(&scene2);
    viewer2->viewport.scene = &scene2;
    node_init(&nodeCube, &cube2);
    node_add_child(&scene2.root, &nodeCube);

    while (running) {
        viewer_update(viewer);
        viewer_update(viewer2);
        usleep(10 * 1000);

        viewer_make_current(viewer);
        dt = viewer_next_frame(viewer);
        t += 50.0 * dt;
        hsv2rgb(fmod(t, 360.0), 1.0, 1.0, color);
        mul3sv(scene.lights.local[0].ambient, 0.1, color);
        mul3sv(scene.lights.local[0].diffuse, 1.0, color);
        viewer_render(viewer);
        material_set_color_vec3(&sphereMat.mat, "color", color);

        viewer_make_current(viewer2);
        viewer_next_frame(viewer2);
        viewer_render(viewer2);
    }

    renderer_free_mesh(viewer->context.renderer, &cubeMesh);
    viewer_free(viewer);
    scene_free(&scene);

    return 0;
}

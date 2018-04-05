#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

#include "viewer.h"
#include "camera.h"
#include "globject.h"
#include "texture.h"
#include "scene.h"
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
    struct GLObject cubeGl2 = {0};
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
    viewer->cursor_callback = cursor_rotate_object;
    viewer->wheel_callback = wheel_callback;
    viewer->key_callback = key_callback;
    viewer->close_callback = close_callback;
    viewer2 = viewer_new(640, 480, "Game 2");
    viewer2->cursor_callback = cursor_rotate_object;
    viewer2->wheel_callback = wheel_callback;
    viewer2->key_callback = key_callback;
    viewer2->close_callback = close_callback;
    running = 1;

    make_box(&cubeMesh, 2.0, 2.0, 2.0);
    viewer_make_current(viewer);
    viewer_make_current(viewer2);
    globject_new(&cubeMesh, &cubeGl2);
    mesh_free(&cubeMesh);

    viewer_make_current(viewer);
    phong_color_material_init(&sphereMat);
    phong_texture_material_init(&textureMat);
    material_set_texture(&textureMat.mat, "tex", asset_manager_load_texture("png/rgb_tux.png"));

    viewer_make_current(viewer2);
    cube2.glObject = cubeGl2;
    solid_texture_material_init(&solidTex);
    matparam_set_texture(&(solidTex.texture), asset_manager_load_texture("png/rgb_tux.png"));
    cube2.material = &solidTex.mat;

    viewer_make_current(viewer);
    scene_init(&scene);
    spheres_and_boxes(&sphereMat.mat, &textureMat.mat, &scene.root);

    test_init_local_light(&scene.lights.local[0]);
    scene.lights.numLocal = 1;

    viewer_make_current(viewer2);
    scene_init(&scene2);
    node_init(&nodeCube, &cube2);
    node_add_child(&scene2.root, &nodeCube);

    viewer->callbackData = &scene.root;
    viewer2->callbackData = &scene2.root;

    while (running) {
        viewer_process_events(viewer);
        viewer_process_events(viewer2);
        usleep(10 * 1000);

        viewer_make_current(viewer);
        dt = viewer_next_frame(viewer);
        t += 50.0 * dt;
        hsv2rgb(fmod(t, 360.0), 1.0, 1.0, color);
        mul3sv(scene.lights.local[0].ambient, 0.1, color);
        mul3sv(scene.lights.local[0].diffuse, 1.0, color);
        scene_render(&scene, viewer);
        material_set_color_vec3(&sphereMat.mat, "color", color);

        viewer_make_current(viewer2);
        viewer_next_frame(viewer2);
        scene_render(&scene2, viewer2);
    }

    globject_free(&cubeGl2);
    viewer_free(viewer);
    scene_free(&scene);

    return 0;
}

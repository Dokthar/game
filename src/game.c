#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

#include "viewer.h"
#include "camera.h"
#include "mesh.h"
#include "globject.h"
#include "texture.h"
#include "geometries/solid_color.h"
#include "geometries/solid_texture.h"

struct Viewer* viewer;
int running;

static void cursor_callback(double xpos, double ypos, double dx, double dy, int buttonLeft, int buttonMiddle, int buttonRight, void* data) {
    Vec3 axis = {0, 1, 0};
    if (buttonLeft) {
        camera_rotate(&viewer->camera, axis, dx / viewer->width);
        camera_get_right(&viewer->camera, axis);
        camera_rotate(&viewer->camera, axis, dy / viewer->height);
    }
}

static void wheel_callback(double xoffset, double yoffset, void* userData) {
    Vec3 axis;
    
    camera_get_backward(&viewer->camera, axis);
    scale3v(axis, -yoffset);
    camera_move(&viewer->camera, axis);
}

static void key_callback(int key, int scancode, int action, int mods, void* userData) {
    Vec3 axis;

    switch (key) {
        case GLFW_KEY_ESCAPE:
            running = 0;
            break;
        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            camera_get_up(&viewer->camera, axis);
            camera_rotate(&viewer->camera, axis, 0.01);
            break;
        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            camera_get_up(&viewer->camera, axis);
            camera_rotate(&viewer->camera, axis, -0.01);
            break;
        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            camera_get_backward(&viewer->camera, axis);
            scale3v(axis, 0.1);
            camera_move(&viewer->camera, axis);
            break;
        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            camera_get_backward(&viewer->camera, axis);
            scale3v(axis, -0.1);
            camera_move(&viewer->camera, axis);
            break;
    }
}

static void close_callback(void* userData) {
    running = 0;
}

int main() {
    double dt;
    struct Mesh cubeMesh = {0};
    struct GLObject cubeGl = {0};
    struct Geometry cube = {0};
    struct SolidTextureGeometry texturedCube = {0};

    viewer = viewer_new(1024, 768, "Game");
    viewer->cursor_callback = cursor_callback;
    viewer->wheel_callback = wheel_callback;
    viewer->key_callback = key_callback;
    viewer->close_callback = close_callback;
    running = 1;

    mesh_load(&cubeMesh, "models/cube.obj", 0, 0, 1);
    globject_new(&cubeMesh, &cubeGl);

    solid_color_geometry(&cube, &cubeGl, 0.0, 0.0, 1.0);
    solid_texture_geometry(&texturedCube, &cubeGl, texture_load_from_file("textures/tux.png"));
    texturedCube.geometry.model[3][1] = 3.0;

    while (running) {
        viewer_process_events(viewer);
        usleep(10 * 1000);

        dt = viewer_next_frame(viewer);
        geometry_render(&cube, &viewer->camera);
        geometry_render(&texturedCube.geometry, &viewer->camera);
    }

    solid_color_shader_free();
    solid_texture_shader_free();
    glDeleteTextures(1, &texturedCube.texture);
    globject_free(&cubeGl);
    mesh_free(&cubeMesh);
    viewer_free(viewer);

    return 0;
}

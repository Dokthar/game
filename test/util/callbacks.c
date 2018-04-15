#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "callbacks.h"
#include "viewer.h"
#include "scene/node.h"
#include "render/camera.h"
#include "math/linear_algebra.h"

int running;

void cursor_rotate_scene(struct Context* ctx, double xpos, double ypos, double dx, double dy, int buttonLeft, int buttonMiddle, int buttonRight) {
    struct Viewer* viewer = ctx->user_data;
    struct Node* scene = &viewer->viewport.scene->root;
    Vec3 x = {0, 1, 0}, y = {1, 0, 0};

    if (buttonLeft) {
        node_rotate(scene, x, 4.0 * dx / ctx->width);
        node_rotate(scene, y, 4.0 * dy / ctx->height);
    }
}

void cursor_rotate_camera(struct Context* ctx, double xpos, double ypos, double dx, double dy, int buttonLeft, int buttonMiddle, int buttonRight) {
    struct Viewer* viewer = ctx->user_data;
    Vec3 axis = {0, 1, 0};

    if (buttonLeft) {
        camera_rotate(&viewer->viewport.camera, axis, dx / ctx->width);
        camera_get_right(&viewer->viewport.camera, axis);
        camera_rotate(&viewer->viewport.camera, axis, dy / ctx->height);
    }
}

void wheel_callback(struct Context* ctx, double xoffset, double yoffset) {
    struct Viewer* viewer = ctx->user_data;
    Vec3 axis;

    camera_get_backward(&viewer->viewport.camera, axis);
    scale3v(axis, -yoffset);
    camera_move(&viewer->viewport.camera, axis);
}

void key_callback(struct Context* ctx, int key, int scancode, int action, int mods) {
    struct Viewer* viewer = ctx->user_data;
    Vec3 axis = {0, 1, 0};

    switch (key) {
        case GLFW_KEY_ESCAPE:
            running = 0;
            break;
        case GLFW_KEY_PAGE_UP:
        case GLFW_KEY_Q:
            camera_get_up(&viewer->viewport.camera, axis);
            scale3v(axis, 0.1);
            camera_move(&viewer->viewport.camera, axis);
            break;
        case GLFW_KEY_PAGE_DOWN:
        case GLFW_KEY_E:
            camera_get_up(&viewer->viewport.camera, axis);
            scale3v(axis, -0.1);
            camera_move(&viewer->viewport.camera, axis);
            break;
        case GLFW_KEY_LEFT:
        case GLFW_KEY_A:
            camera_get_right(&viewer->viewport.camera, axis);
            scale3v(axis, -0.1);
            camera_move(&viewer->viewport.camera, axis);
            break;
        case GLFW_KEY_RIGHT:
        case GLFW_KEY_D:
            camera_get_right(&viewer->viewport.camera, axis);
            scale3v(axis, 0.1);
            camera_move(&viewer->viewport.camera, axis);
            break;
        case GLFW_KEY_DOWN:
        case GLFW_KEY_S:
            camera_get_backward(&viewer->viewport.camera, axis);
            scale3v(axis, 0.1);
            camera_move(&viewer->viewport.camera, axis);
            break;
        case GLFW_KEY_UP:
        case GLFW_KEY_W:
            camera_get_backward(&viewer->viewport.camera, axis);
            scale3v(axis, -0.1);
            camera_move(&viewer->viewport.camera, axis);
            break;
        case GLFW_KEY_F12:
            viewer_screenshot(viewer, "screenshot.png");
            break;
    }
}

void close_callback(struct Context* ctx) {
    running = 0;
}


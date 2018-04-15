#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glfw3_context.h"
#include "render/renderer.h"

static void cursor_event(GLFWwindow* window, double xpos, double ypos) {
    struct Context* ctx = glfwGetWindowUserPointer(window);
    int buttonLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    int buttonMiddle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
    int buttonRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    double dx = xpos - ctx->last_x;
    double dy = ypos - ctx->last_y;
    ctx->last_x = xpos;
    ctx->last_y = ypos;

    if (ctx->cursor_callback) {
        ctx->cursor_callback(ctx, xpos, ypos, dx, dy, buttonLeft, buttonMiddle, buttonRight);
    }
}

static void scroll_event(GLFWwindow* window, double xoffset, double yoffset) {
    struct Context* ctx = glfwGetWindowUserPointer(window);

    if (ctx->wheel_callback) {
        ctx->wheel_callback(ctx, xoffset, yoffset);
    }
}

static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods) {
    struct Context* ctx = glfwGetWindowUserPointer(window);

    if (ctx->key_callback) {
        ctx->key_callback(ctx, key, scancode, action, mods);
    }
}

static void resize_event(GLFWwindow* window, int width, int height) {
    struct Context* ctx = glfwGetWindowUserPointer(window);

    ctx->width = width;
    ctx->height = height;
    if (ctx->resize_callback) {
        ctx->resize_callback(ctx, width, height);
    }
}

static void close_event(GLFWwindow* window) {
    struct Context* ctx = glfwGetWindowUserPointer(window);

    if (ctx->close_callback) {
        ctx->close_callback(ctx);
    }
}

static void glfw3_context_create(struct Context* ctx) {
    GLFWwindow* window;
    const char* title = ctx->settings->title;
    ctx->width = ctx->settings->width;
    ctx->height = ctx->settings->height;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(ctx->width, ctx->height, title, NULL, NULL);

    if (!window) {
        fprintf(stderr, "Error: window creation failed\n");
        return;
    }

    glfwMakeContextCurrent(window);
    ctx->priv_data = window;
    glfwSetWindowUserPointer(window, ctx);

    /* Inputs */
    glfwSetKeyCallback(window, key_event);
    glfwSetCursorPosCallback(window, cursor_event);
    glfwSetScrollCallback(window, scroll_event);
    glfwSetWindowSizeCallback(window, resize_event);
    glfwSetWindowCloseCallback(window, close_event);

    /*glfwSetInputMode(viewer->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/
    glewExperimental = 1;
    if (glGetError() != GL_NO_ERROR) {
	fprintf(stderr, "Error: GL context setup failed\n");
    } else if (glewInit() != GLEW_OK) {
	fprintf(stderr, "Error: GLEW initialization failed\n");
    }

    renderer_init(ctx->renderer);
}

static void glfw3_context_destroy(struct Context* ctx) {
    GLFWwindow* window = ctx->priv_data;

    if (window) {
        renderer_destroy(ctx->renderer);
        free(ctx->renderer);
        glfwDestroyWindow(window);
    }
}

static void glfw3_set_title(struct Context* ctx, const char* title) {
    GLFWwindow* window = ctx->priv_data;

    if (window) {
        glfwSetWindowTitle(window, title);
    }
}

static void glfw3_update(struct Context* ctx) {
    GLFWwindow* window = ctx->priv_data;

    if (window) {
	glfwPollEvents();
    }
}

static double glfw3_swap_buffer(struct Context* ctx) {
    GLFWwindow* window = ctx->priv_data;

    ctx->last_time = ctx->time;
    ctx->time = glfwGetTime();
    ctx->tpf = ctx->time - ctx->last_time;

    if (window) {
         glfwSwapBuffers(window);
    }

    return ctx->tpf;
}

static void glfw3_make_current(struct Context* ctx) {
    GLFWwindow* window = ctx->priv_data;

    if (window) {
        glfwMakeContextCurrent(window);
    }
}

void glfw3_context_init(struct Context* ctx, struct Settings* settings) {
    if (!glfwInit()) {
        fprintf(stderr, "Error: GLFW3 initialization failed\n");
	return;
    }
    ctx->settings = settings;
    ctx->create = glfw3_context_create;
    ctx->destroy = glfw3_context_destroy;
    ctx->set_title = glfw3_set_title;
    ctx->swap_buffer = glfw3_swap_buffer;
    ctx->update = glfw3_update;
    ctx->make_current = glfw3_make_current;

    ctx->renderer = calloc(1, sizeof(struct Renderer));
}

void glfw3_context_terminate() {
    glfwTerminate();
}

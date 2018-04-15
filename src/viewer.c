#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "viewer.h"
#include "img/png.h"
#include "material/shaders.h"
#include "glfw3/glfw3_context.h"

struct ViewerImpl {
    struct Viewer user;
    int hasLast;
    double lastX, lastY;
    double lastTime;
    GLuint shaders[NUM_SHADERS];
};

static void resize_callback(struct Context* ctx, int width, int height) {
    struct Viewer* viewer = ctx->user_data;

    if (viewer) {
        camera_resize(&viewer->viewport.camera, width, height, 1);
        camera_update_projection(&viewer->viewport.camera);
    }
}

struct Viewer* viewer_new(unsigned int width, unsigned int height, const char* title) {
    struct ViewerImpl *viewer;
    viewer = malloc(sizeof(struct ViewerImpl));

    if (!viewer) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return NULL;
    }

    viewer->user.settings.width = width;
    viewer->user.settings.height = height;
    viewer->user.settings.title = title;

    glfw3_context_init(&viewer->user.context, &viewer->user.settings);
    viewer->user.context.create(&viewer->user.context);
    viewer->user.context.user_data = &viewer->user;
    viewer->user.context.resize_callback = resize_callback;
    viewer->user.context.make_current(&viewer->user.context);

    if (!game_load_shaders(viewer->shaders)) {
        fprintf(stderr, "Error: failed to load internal shaders\n");
        viewer_free(&viewer->user);
        return NULL;
    } else {
        Vec3 pos = {0, 0, 10};
        camera_load_default(&viewer->user.viewport.camera, pos, ((float)width) / ((float)height));
        viewer_make_current(&viewer->user);
    }

    return &viewer->user;
}

void viewer_free(struct Viewer* viewer) {
    if (viewer) {
        game_free_shaders(((struct ViewerImpl*)viewer)->shaders);
	viewer->context.destroy(&viewer->context);
	glfw3_context_terminate();
        free(viewer);
    }
}

void viewer_make_current(struct Viewer* viewer) {
    viewer->context.make_current(&viewer->context);
    game_shaders = ((struct ViewerImpl*)viewer)->shaders;
}

double viewer_next_frame(struct Viewer* viewer) {
    double dt;

    dt = viewer->context.swap_buffer(&viewer->context);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return dt;
}

int viewer_update(struct Viewer* viewer) {
    viewer->context.update(&viewer->context);
}

int viewer_render(struct Viewer* viewer) {
    return render_viewport(viewer->context.renderer, &viewer->viewport);
}

#define ALIGN 4
int viewer_screenshot(struct Viewer* viewer, const char* filename) {
    unsigned char* data;
    unsigned int rowStride;
    /* use lastest "viewport" dimesions */
    unsigned int width = viewer->context.width;
    unsigned int height = viewer->context.height;
    int ret;

    rowStride = 3 * width;
    if (rowStride % ALIGN) {
        rowStride += ALIGN - (rowStride % ALIGN);
    }

    if (!(data = malloc(rowStride * height))) {
        fprintf(stderr, "Error: cannot allocate memory for screenshot\n");
        return 0;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    ret = png_write(filename, ALIGN, width, height, 0, 1, data);
    free(data);
    return ret;
}

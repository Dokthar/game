#ifndef VIEWER_H
#define VIEWER_H

#include "render/viewport.h"
#include "render/renderer.h"
#include "render/context.h"

struct Viewer {
    struct ViewPort viewport;
    struct Context context;
    struct Settings settings;
};

struct Viewer* viewer_new(unsigned int width, unsigned int height, const char* title);

int viewer_render(struct Viewer* viewer);
int viewer_update(struct Viewer* viewer);
void viewer_make_current(struct Viewer* viewer);
void viewer_free(struct Viewer* viewer);

double viewer_next_frame(struct Viewer* viewer);
int viewer_screenshot(struct Viewer* viewer, const char* filename);

#endif

#ifndef RENDERER_H
#define RENDERER_H

#include "viewport.h"
#include "statistics.h"
#include "render_state.h"

struct Renderer {
    struct Statistics stats;
    struct RenderState ctx;
};

int render_viewport(struct Renderer* rdr, struct ViewPort* view);
int renderer_init(struct Renderer* rdr);
int renderer_destroy(struct Renderer* rdr);

#endif

#ifndef RENDERER_H
#define RENDERER_H

#include "viewport.h"
#include "statistics.h"
#include "render_state.h"
#include "mesh/mesh.h"

#define CONFIG_STATISTICS

struct Renderer {
    struct RenderState ctx;
    unsigned int last_width;
    unsigned int last_height;
#ifdef CONFIG_STATISTICS
    unsigned int update_stats;
    struct Statistics stats;
#endif
};

int render_viewport(struct Renderer* rdr, struct ViewPort* view);
int renderer_init(struct Renderer* rdr);
int renderer_destroy(struct Renderer* rdr);

void renderer_load_mesh(struct Renderer* rdr, struct Mesh* mesh);
void renderer_free_mesh(struct Renderer* rdr, struct Mesh* mesh);


#endif

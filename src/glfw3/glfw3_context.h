#ifndef GLFW3_CONTEXT
#define GLFW3_CONTEXT

#include "render/context.h"

void glfw3_context_init(struct Context* ctx, struct Settings* settings);
void glfw3_context_terminate();

#endif

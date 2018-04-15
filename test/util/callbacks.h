#ifndef TEST_UTIL_CALLBACKS_H
#define TEST_UTIL_CALLBACKS_H
#include "viewer.h"

extern int running;

void cursor_rotate_scene(struct Context* ctx, double xpos, double ypos, double dx, double dy, int buttonLeft, int buttonMiddle, int buttonRight);
void cursor_rotate_camera(struct Context* ctx, double xpos, double ypos, double dx, double dy, int buttonLeft, int buttonMiddle, int buttonRight);
void wheel_callback(struct Context* ctx, double xoffset, double yoffset);
void key_callback(struct Context* ctx, int key, int scancode, int action, int mods);
void close_callback(struct Context* ctx);

#endif

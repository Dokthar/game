#include "render_state.h"

const struct BlendFunction BLEND_FUNC_ADDITIVE = {
    GL_ONE, GL_ONE };

const struct BlendFunction BLEND_FUNC_ALPHA_ADDITIVE = {
    GL_SRC_ALPHA, GL_ONE };

const struct BlendFunction BLEND_FUNC_ALPHA = {
    GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

const struct BlendFunction BLEND_FUNC_PREMULT_ALPHA = {
    GL_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

const struct BlendFunction BLEND_FUNC_MODULATE = {
    GL_DST_COLOR, GL_ZERO };

const struct BlendFunction BLEND_FUNC_MODULATE_TIMES_2 = {
    GL_DST_COLOR, GL_SRC_COLOR };

const struct BlendFunction BLEND_FUNC_COLOR = {
    GL_ONE, GL_ONE_MINUS_SRC_COLOR };

const struct BlendFunction BLEND_FUNC_SCREEN = {
    GL_ONE, GL_ONE_MINUS_SRC_COLOR };

const struct BlendFunction BLEND_FUNC_EXCLUSION = {
    GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR };

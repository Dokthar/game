#ifndef RENDER_STATE
#define RENDER_STATE

#include <GL/gl.h>

/*
 * In order to use the depth test, the current Framebuffer must have a depth
 * buffer AND the depth test must be enabled.
 * A depth test compare the depth value from fragment against the depth value
 * form framebuffer.
 * Documentation: https://www.khronos.org/opengl/wiki/Depth_Test
 *
 * The test is of the form:
 * if (TEST_FUNC) {
 *     update depth
 * } else {
 *     discard fragment
 * }
 * Where TEST_FUNC is specified by:
 */
enum TestFunction {
    TEST_OFF = 0,
    /* FALSE */
    TEST_NEVER = GL_NEVER,
    /* frag_depth < frame_depth */
    TEST_LESS = GL_LESS,
    /* frag_depth == frame_depth */
    TEST_EQUAL = GL_EQUAL,
    /* frag_depth <= frame_depth */
    TEST_LESS_EQUAL = GL_LEQUAL,
    /* frag_depth > frame_depth */
    TEST_GREATER = GL_GREATER,
    /* frag_depth != frame_depth */
    TEST_NOT_EQUAL = GL_EQUAL,
    /* frag_depth >= frame_depth */
    TEST_GREATER_EQUAL = GL_GEQUAL,
    /* TRUE */
    TEST_ALWAYS = GL_ALWAYS
};

/*
 * Documentation http://docs.gl/gl3/glBlendFuncSeparate
 */
enum BlendFactor {
    BLEND_ZERO = GL_ZERO,
    BLEND_ONE = GL_ONE,
    BLEND_SRC_COLOR = GL_SRC_COLOR,
    BLEND_ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
    BLEND_DST_COLOR = GL_DST_COLOR,
    BLEND_ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
    BLEND_SRC_ALPHA = GL_SRC_ALPHA,
    BLEND_ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
    BLEND_DST_ALPHA = GL_DST_ALPHA,
    BLEND_ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
    /* CONSTANT is set by glBlendColor() */
    BLEND_CONSTANT_COLOR = GL_CONSTANT_COLOR,
    BLEND_ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
    BLEND_CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
    BLEND_ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
    BLEND_SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE,
    /* openGL 3 extension : */
    BLEND_SRC1_COLOR = GL_SRC1_COLOR,
    BLEND_ONE_MINUS_SRC1_COLOR = GL_ONE_MINUS_SRC1_COLOR,
    BLEND_SRC1_ALPHA = GL_SRC1_ALPHA,
    BLEND_ONE_MINUS_SRC1_ALPHA = GL_ONE_MINUS_SRC1_ALPHA
};

struct BlendFunction {
    enum BlendFactor src_factor;
    enum BlendFactor dst_factor;
    enum BlendFactor src_factor_alpha;
    enum BlendFactor dst_factor_alpha;
    struct {
        unsigned int separate_function:1;
    } flags;
};

/* various predefined blend functions */
extern const struct BlendFunction BLEND_FUNC_ADDITIVE;
extern const struct BlendFunction BLEND_FUNC_ALPHA_ADDITIVE;
extern const struct BlendFunction BLEND_FUNC_PREMULT_ALPHA;
extern const struct BlendFunction BLEND_FUNC_ALPHA;
extern const struct BlendFunction BLEND_FUNC_MODULATE;
extern const struct BlendFunction BLEND_FUNC_MODULATE_TIMES_2;
extern const struct BlendFunction BLEND_FUNC_COLOR;
extern const struct BlendFunction BLEND_FUNC_SCREEN;
extern const struct BlendFunction BLEND_FUNC_EXCLUSION;

enum FaceCull {
    CULL_OFF = 0,
    CULL_BACK_FACE = GL_BACK,
    CULL_FRONT_FACE = GL_FRONT,
    CULL_ALL_FACE = GL_FRONT_AND_BACK
};

/* polygon rasterization mode */
enum PolygonMode {
    MODE_POINT = GL_POINT,
    MODE_LINE = GL_LINE,
    MODE_FILL = GL_FILL
};

struct RenderState {
    enum FaceCull culling;
    enum PolygonMode mode;
    float point_size;
    float line_width;
    enum TestFunction depth_func;
    struct BlendFunction blend_func;
    struct {
	unsigned int blend_enabled:1;
	unsigned int face_cull_enabled:1;
	unsigned int depth_test_enabled:1;
	unsigned int depth_write_enabled:1;
	unsigned int antialiasing_enabled:1;
	unsigned int line_smooth_enabled:1;
    } flags;
};

#endif

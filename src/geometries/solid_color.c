#include "solid_color.h"
#include "shader.h"
#include <stdlib.h>

static GLuint shader = 0;

struct params {
    Vec3 color;
};

static void draw_solid_color(const struct Geometry* geometry) {
    struct params *pdata = (struct params *)geometry->priv_data;

    glUniform3fv(glGetUniformLocation(geometry->shader, "solidColor"), 1, pdata->color);
    glDrawArrays(GL_TRIANGLES, 0, geometry->glObject.numVertices);
}

void solid_color_geometry(struct Geometry* dest, const struct GLObject* glObject, float r, float g, float b) {
    struct params *pdata;

    load_id4(dest->model);
    if (!shader) {
        shader = shader_compile("shaders/solid_color.vert", "shaders/solid_color.frag");
    }
    dest->shader = shader;
    dest->glObject = *glObject;
    dest->render = draw_solid_color;

    pdata = malloc(sizeof(struct params));

    pdata->color[0] = r;
    pdata->color[1] = g;
    pdata->color[2] = b;

    dest->priv_data = pdata;
}

void solid_color_shader_free(void) {
    glDeleteProgram(shader);
}

#include "solid_texture.h"
#include "shader.h"
#include <stdlib.h>

static GLuint shader = 0;

struct params {
	GLuint texture;
};

static void draw_solid_texture(const struct Geometry* geometry) {
    struct params *pdata = (struct params *)geometry->priv_data;

    glBindTexture(GL_TEXTURE_2D, pdata->texture);
    glDrawArrays(GL_TRIANGLES, 0, geometry->glObject.numVertices);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void solid_texture_geometry(struct Geometry* dest, const struct GLObject* glObject, GLuint texture) {
    struct params *pdata;

    load_id4(dest->model);
    if (!shader) {
        shader = shader_compile("shaders/solid_texture.vert", "shaders/solid_texture.frag");
    }
    dest->shader = shader;
    dest->glObject = *glObject;
    dest->render = draw_solid_texture;

    pdata = malloc(sizeof(struct params));

    pdata->texture = texture;

    dest->priv_data = pdata;
}

void solid_texture_shader_free(void) {
    glDeleteProgram(shader);
}

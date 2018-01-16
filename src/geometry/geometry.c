#include "geometry.h"

void geometry_render(const struct Geometry* geometry, const struct Camera* camera, Mat4 model) {
    struct Material *mat = geometry->material;
    glUseProgram(mat->shader);
    glBindVertexArray(geometry->glObject.vao);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "projection"), 1, GL_FALSE, (float*)camera->projection);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "view"), 1, GL_FALSE, (float*)camera->view);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "model"), 1, GL_FALSE, (float*)model);
    glPolygonMode(GL_FRONT_AND_BACK, mat->mode);
    if (mat->prerender) {
	    mat->prerender(mat, camera);
    }
    if (geometry->glObject.numIndices) {
        glDrawElements(GL_TRIANGLES, geometry->glObject.numIndices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, geometry->glObject.numVertices);
    }
    if (mat->postrender) {
        mat->postrender(mat, camera);
    }
    glBindVertexArray(0);
    glUseProgram(0);
}

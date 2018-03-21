#include "geometry.h"

void geometry_render(const struct Geometry* geometry, const struct Camera* camera, const struct Lights* lights, Mat4 model, Mat3 inverseNormal) {
    struct Material* mat = geometry->material;

    glUseProgram(mat->shader);
    glBindVertexArray(geometry->glObject.vao);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "projection"), 1, GL_FALSE, (float*)camera->projection);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "view"), 1, GL_FALSE, (float*)camera->view);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "model"), 1, GL_FALSE, (float*)model);
    glUniformMatrix3fv(glGetUniformLocation(mat->shader, "inverseNormal"), 1, GL_FALSE, (float*)inverseNormal);
    glPolygonMode(GL_FRONT_AND_BACK, mat->mode);
    if (mat->prerender) {
        mat->prerender(mat, camera, lights);
    }
    if (geometry->glObject.numIndices) {
        glDrawElements(GL_TRIANGLES, geometry->glObject.numIndices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, geometry->glObject.numVertices);
    }
    if (mat->postrender) {
        mat->postrender(mat, camera, lights);
    }
    glBindVertexArray(0);
    glUseProgram(0);
}

#include <GL/glew.h>
#include <stdio.h>
#include "renderer.h"
#include "gl/globject.h"

void material_update_params(const struct Material *mat) {
    unsigned int i;
    struct Matparam param;
    GLint location;

    for (i = 0; i < mat->nb_params; i++) {
        param = mat->params[i];
        location = glGetUniformLocation(mat->shader, param.name);
        switch (param.type) {
        case INT:
            glUniform1i(location, param.value._int);
            break;
        case FLOAT:
            glUniform1f(location, param.value._float);
            break;
        case VEC2:
            glUniform2fv(location, 1, param.value._vec2);
            break;
        case VEC3:
            glUniform3fv(location, 1, param.value._vec3);
            break;
        case VEC4:
            glUniform4fv(location, 1, param.value._vec4);
            break;
        case TEXTURE:
            glBindTexture(GL_TEXTURE_2D, param.value._texture);
            break;
        }
    }
}


void render_geometry(const struct Geometry* geometry, const struct Camera* camera, const struct Lights* lights, Mat4 model, Mat3 inverseNormal) {
    const struct Material* mat = geometry->material;

    glUseProgram(mat->shader);

    glBindVertexArray(geometry->glObject.vao);

    glPolygonMode(GL_FRONT_AND_BACK, mat->mode);

    light_load_uniforms(mat->shader, lights->directional, lights->numDirectional, lights->local, lights->numLocal);

    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "projection"), 1, GL_FALSE, (float*)camera->projection);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "view"), 1, GL_FALSE, (float*)camera->view);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "model"), 1, GL_FALSE, (float*)model);
    glUniformMatrix3fv(glGetUniformLocation(mat->shader, "inverseNormal"), 1, GL_FALSE, (float*)inverseNormal);

    material_update_params(mat);

    if (geometry->glObject.numIndices) {
        glDrawElements(GL_TRIANGLES, geometry->glObject.numIndices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, geometry->glObject.numVertices);
    }

    glBindVertexArray(0);
    glUseProgram(0);
}

int render_graph(struct Node* node, const struct Camera* cam, const struct Lights* lights) {
    unsigned int i;
    int res = 1;

    node_update_matrices(node);

    if (node->geometry) {
	render_geometry(node->geometry, cam, lights, node->model, node->inverseNormal);
    }

    for (i = 0; i < node->nbChildren && res; i++) {
        res = res && render_graph(node->children[i], cam, lights);
    }

    return res;
}

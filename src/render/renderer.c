#include <GL/glew.h>
#include <stdio.h>
#include "renderer.h"
#include "gl/globject.h"

/* TODO: shader/program abstraction
   void set_shader(struct Renderer* rdr, Shader shader); */
/* TODO: texture abstraction
   void set_texture(struct Renderer* rdr, int unit, Texture tex); */
/* TODO: Mesh abstraction
   void render_mesh(struct Renderer* rdr, Mesh mesh); */

void set_depth_test(struct Renderer* rdr, int enable) {
    if (enable) {
        rdr->ctx.flags.depth_test_enabled = 1;
        glEnable(GL_DEPTH_TEST);
    } else {
        rdr->ctx.flags.depth_test_enabled = 0;
        glDisable(GL_DEPTH_TEST);
    }
}

void set_depth_function(struct Renderer* rdr, enum TestFunction func) {
    glDepthFunc(func);
}

void set_blend_function(struct Renderer* rdr, struct BlendFunction* func) {
    struct BlendFunction* cf = &rdr->ctx.blend_func;

    if (!func) {
        rdr->ctx.flags.blend_enabled = 1;
        glDisable(GL_BLEND);
        return;
    } else if (rdr->ctx.flags.blend_enabled == 0) {
        rdr->ctx.flags.blend_enabled = 1;
        glEnable(GL_BLEND);
    }

    if (func->flags.separate_function) {
        if (cf->src_factor != func->src_factor
            || cf->dst_factor != func->dst_factor
            || cf->src_factor_alpha != func->src_factor_alpha
            || cf->dst_factor_alpha != func->dst_factor_alpha) {
            *cf = *func;
            glBlendFuncSeparate(func->src_factor, func->dst_factor,
                    func->src_factor_alpha, func->dst_factor_alpha);
        }
    } else {
            *cf = *func;
            cf->src_factor_alpha = func->src_factor;
            cf->dst_factor_alpha = func->dst_factor;
            glBlendFunc(func->src_factor, func->dst_factor);
    }
}

void set_face_culling(struct Renderer* rdr, enum FaceCull cull) {
    if (cull == CULL_OFF) {
        rdr->ctx.flags.face_cull_enabled = 0;
        glDisable(GL_CULL_FACE);
    } else if (rdr->ctx.flags.face_cull_enabled == 0) {
        rdr->ctx.flags.face_cull_enabled = 1;
        glEnable(GL_CULL_FACE);
    }
    if (rdr->ctx.culling != cull) {
        rdr->ctx.culling = cull;
        glCullFace(cull);
    }
}

void set_polygon_mode(struct Renderer* rdr, enum PolygonMode mode) {
    if (rdr->ctx.mode != mode) {
        rdr->ctx.mode = mode;
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}

/* dont:        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
   deprecated ? glEnable(GL_TEXTURE_2D);
*/
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

void render_geometry(struct Renderer* r, const struct Geometry* geometry, const struct Camera* camera, const struct Lights* lights, Mat4 model, Mat3 inverseNormal) {
    const struct Material* mat = geometry->material;

    glUseProgram(mat->shader);

    glBindVertexArray(geometry->glObject.vao);

    set_polygon_mode(r, mat->mode);

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
}

int render_graph(struct Renderer* rm, struct Node* node, const struct Camera* cam, const struct Lights* lights) {
    unsigned int i;
    int res = 1;

    node_update_matrices(node);

    if (node->geometry) {
	render_geometry(rm, node->geometry, cam, lights, node->model, node->inverseNormal);
    }

    for (i = 0; i < node->nbChildren && res; i++) {
        res = res && render_graph(rm, node->children[i], cam, lights);
    }

    return res;
}

int render_viewport(struct Renderer* render, struct ViewPort* view) {
    return render_graph(render, &view->scene->root, &view->camera, &view->scene->lights);
}

int renderer_init(struct Renderer* rdr) {
    set_depth_test(rdr, 1);
    set_depth_function(rdr, TEST_LESS);
    set_blend_function(rdr, &BLEND_FUNC_ALPHA);
    /*
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_TEXTURE_2D);
    */
    glEnable(GL_MULTISAMPLE);
}

int renderer_destroy(struct Renderer* rdr) {
    /* TODO: free all gl objects */
}
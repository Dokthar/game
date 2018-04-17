#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"
#include "gl/globject.h"

/* TODO: shader/program abstraction
   void set_shader(struct Renderer* rdr, Shader shader); */
/* TODO: texture abstraction
   void set_texture(struct Renderer* rdr, int unit, Texture tex); */

void renderer_load_mesh(struct Renderer* rdr, struct Mesh* mesh) {
    struct GLObject* obj = malloc(sizeof(struct GLObject));

    mesh->render_data = obj;
    globject_new(mesh, obj);
#ifdef CONFIG_STATISTICS
    if (rdr->update_stats) {
        rdr->stats.nbVboMemory += obj->numVBOs;
    }
#endif
}

void renderer_free_mesh(struct Renderer* rdr, struct Mesh* mesh) {
    struct GLObject* obj = mesh->render_data;

#ifdef CONFIG_STATISTICS
    if (rdr->update_stats) {
        rdr->stats.nbVboMemory -= obj->numVBOs;
    }
#endif
    globject_free(obj);
    mesh->render_data = NULL;
}

static void render_mesh(struct Renderer* rdr, struct Mesh* mesh) {
    struct GLObject* obj;

    if (mesh->render_data == NULL) {
        renderer_load_mesh(rdr, mesh);
    }
    obj = mesh->render_data;

    glBindVertexArray(obj->vao);

    if (obj->numIndices) {
        glDrawElements(GL_TRIANGLES, obj->numIndices, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, obj->numVertices);
    }
#ifdef CONFIG_STATISTICS
    if (rdr->update_stats) {
        rdr->stats.nbVertices += obj->numVertices;
        rdr->stats.nbTriangles += obj->numVertices/3;
        rdr->stats.nbVboMemory -= obj->numVBOs;
    }
#endif
}

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

    set_polygon_mode(r, mat->mode);

    light_load_uniforms(mat->shader, lights->directional, lights->numDirectional, lights->local, lights->numLocal);

    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "projection"), 1, GL_FALSE, (float*)camera->projection);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "view"), 1, GL_FALSE, (float*)camera->view);
    glUniformMatrix4fv(glGetUniformLocation(mat->shader, "model"), 1, GL_FALSE, (float*)model);
    glUniformMatrix3fv(glGetUniformLocation(mat->shader, "inverseNormal"), 1, GL_FALSE, (float*)inverseNormal);

    material_update_params(mat);

    render_mesh(r, geometry->mesh);
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
#ifdef CONFIG_STATISTICS
    if (render->update_stats) {
        render->stats.nbTriangles = 0;
        render->stats.nbVertices = 0;
        render->stats.nbUniformsSet = 0;
        render->stats.nbShaderSwitches = 0;
        render->stats.nbShaderFrame = 0;
        render->stats.nbTextureSwitches = 0;
        render->stats.nbTextureFrame = 0;
    }
#endif

    if (view->camera.width != render->last_width
        || view->camera.height != render->last_height) {
        render->last_width = view->camera.width;
        render->last_height = view->camera.height;
        glViewport(0, 0, view->camera.width, view->camera.height);
    }
    return render_graph(render, &view->scene->root, &view->camera, &view->scene->lights);
}

int renderer_init(struct Renderer* rdr) {
    set_depth_test(rdr, 1);
    set_depth_function(rdr, TEST_LESS);
    set_blend_function(rdr, &BLEND_FUNC_ALPHA);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_TEXTURE_2D);
    rdr->update_stats = 1;
    memset(&rdr->stats, 0, sizeof(struct Statistics));
}

int renderer_destroy(struct Renderer* rdr) {
    /* TODO: free all gl objects */
}

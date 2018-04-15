#include <string.h>
#include <math.h>
#include "camera.h"

static void camera_update_position(struct Camera* camera) {
    camera->view[3][0] = -(camera->view[0][0] * camera->position[0] + camera->view[1][0] * camera->position[1] + camera->view[2][0] * camera->position[2]);
    camera->view[3][1] = -(camera->view[0][1] * camera->position[0] + camera->view[1][1] * camera->position[1] + camera->view[2][1] * camera->position[2]);
    camera->view[3][2] = -(camera->view[0][2] * camera->position[0] + camera->view[1][2] * camera->position[1] + camera->view[2][2] * camera->position[2]);
}

static void camera_update_orientation(struct Camera* camera) {
    Mat3 rot;
    quaternion_to_mat3(rot, camera->orientation);
    transpose3m(rot);
    mat3to4(camera->view, rot);
}

void camera_load_default(struct Camera* camera, Vec3 pos, float ratio) {
    memcpy(camera->position, pos, sizeof(Vec3));
    quaternion_load_id(camera->orientation);
    load_id4(camera->view);
    load_id4(camera->projection);

    camera->orthographic = 0;
    frustum_from_fov(&camera->frustum, 1.04, ratio, 0.1, 2000);

    camera_update_view(camera);
    camera_update_projection(camera);
}

void camera_get_right(struct Camera* camera, Vec3 right) {
    row3m4(right, camera->view, 0);
}

void camera_get_up(struct Camera* camera, Vec3 up) {
    row3m4(up, camera->view, 1);
}

void camera_get_backward(struct Camera* camera, Vec3 backward) {
    row3m4(backward, camera->view, 2);
}

void camera_move(struct Camera* camera, Vec3 translation) {
    incr3v(camera->position, translation);
    camera_update_orientation(camera);
    camera_update_position(camera);
}

void camera_rotate(struct Camera* camera, Vec3 axis, float angle) {
    Quaternion q, old;
    quaternion_set_axis_angle(q, axis, angle);
    memcpy(old, camera->orientation, sizeof(Quaternion));
    quaternion_mul(camera->orientation, q, old);
    camera_update_orientation(camera);
    camera_update_position(camera);
}

void camera_update_view(struct Camera* camera) {
    camera_update_orientation(camera);
    camera_update_position(camera);
}

void frustum_from_fov(struct Frustum* frustum, float hfov, float ratio, float near, float far) {
    float h = tan(hfov * 0.5) * near;
    float w = h * ratio;

    frustum->left = -w;
    frustum->right = w;
    frustum->bottom = -h;
    frustum->top = h;
    frustum->near = near;
    frustum->far = far;
}

void camera_resize(struct Camera* camera, int width, int height, int preserve_ratio) {
    struct Frustum* f = &camera->frustum;
    float ratio;
    camera->width = width;
    camera->height = height;

    if (preserve_ratio) {
	ratio = ((float) width) / ((float) height);
	f->right = f->top * ratio;
	f->left = -f->right;
    }
}

void perspective_projection(const struct Frustum* F, Mat4 proj) {
    const float a =  (F->right + F->left) / (F->right - F->left);
    const float b =  (F->top + F->bottom) / (F->top - F->bottom);
    const float c = -(F->far + F->near) / (F->far - F->near);
    const float d = -(2.0 * F->far * F->near) / (F->far - F->near);
    const float e =  (2.0 * F->near) / (F->right - F->left);
    const float f =  (2.0 * F->near) / (F->top - F->bottom);

    memset(proj, 0, sizeof(Mat4));

    /* Projection matrix:
     *  [ e  0  a  0 ]
     *  [ 0  f  b  0 ]
     *  [ 0  0  c  d ]
     *  [ 0  0 -1  0 ]
     */
    proj[0][0] = e;
    proj[1][1] = f;
    proj[2][0] = a;
    proj[2][1] = b;
    proj[2][2] = c;
    proj[2][3] = -1.0;
    proj[3][2] = d;
}

void orthographic_projection(const struct Frustum* F, Mat4 proj) {
    const float a = -(F->right + F->left) / (F->right - F->left);
    const float b = -(F->top + F->bottom) / (F->top - F->bottom);
    const float c = -(F->far + F->near) / (F->far - F->near);
    const float d =  2.0 / (F->right - F->left);
    const float e =  2.0 / (F->top - F->bottom);
    const float f =  2.0 / (F->far - F->near);

    memset(proj, 0, sizeof(Mat4));

    /* Projection matrix:
     *  [ d  0  0  a ]
     *  [ 0  e  0  b ]
     *  [ 0  0  f  c ]
     *  [ 0  0  0  1 ]
     */
    proj[0][0] = d;
    proj[1][1] = e;
    proj[2][2] = f;
    proj[3][0] = a;
    proj[3][1] = b;
    proj[3][2] = c;
    proj[3][3] = 1.0;
}

void camera_update_projection(struct Camera* camera) {
    if (camera->orthographic) {
	orthographic_projection(&camera->frustum, camera->projection);
    } else {
	perspective_projection(&camera->frustum, camera->projection);
    }
}

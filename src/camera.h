#ifndef CAMERA_H
#define CAMERA_H
#include "linear_algebra.h"
#include "quaternion.h"

struct Frustum {
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;
};

struct Camera {
    Vec3 position;
    Quaternion orientation;
    struct Frustum frustum;
    int width;
    int height;
    int orthographic;
    Mat4 projection;
    Mat4 view;
};

void camera_load_default(struct Camera* camera, Vec3 pos, float ratio);

void camera_get_right(struct Camera* camera, Vec3 right);
void camera_get_up(struct Camera* camera, Vec3 up);
void camera_get_backward(struct Camera* camera, Vec3 backward);

void camera_move(struct Camera* camera, Vec3 translation);
void camera_rotate(struct Camera* camera, Vec3 axis, float angle);

void camera_set_fov(struct Camera* camera, float fov);
void camera_resize(struct Camera* camera, int width, int height, int preserve_ratio);

void camera_update_view(struct Camera* camera);
void camera_update_projection(struct Camera* camera);

void frustum_from_fov(struct Frustum* frustum, float hfov, float ratio, float near, float far);

#endif

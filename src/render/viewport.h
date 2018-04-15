#ifndef VIEW_PORT_H
#define VIEW_PORT_H
#include "camera.h"
#include "scene/scene.h"

struct ViewPort {
    /* The camera associated with this viewport */
    struct Camera camera;
    /* The scene to render through this viewport, can be shared */
    struct Scene* scene;
};

#endif

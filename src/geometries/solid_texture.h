#include "geometry.h"

#ifndef SOLID_TEXTURE_H
#define SOLID_TEXTURE_H

void solid_texture_geometry(struct Geometry* dest, const struct GLObject* glObject, GLuint texture);

void solid_texture_shader_free(void);

#endif

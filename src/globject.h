#include <GL/glew.h>

#ifndef GLOBJECT_H
#define GLOBJECT_H

struct GLObject
{
    GLuint vbo[4], vao;
    unsigned int numVBOs;
};

#endif

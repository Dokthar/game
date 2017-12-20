#ifndef ASSETS_H
#define ASSETS_H

#include <GL/glew.h>
#include "globject.h"

enum Model {
	TEST_CUBE = 0,
	TETRAPOD,
	NB_MODELS
};

enum Texture {
	NB_TEXTURES = 1
};

enum Shader {
	SOLID_COLOR = 0,
	NB_SHADERS
};

GLuint load_texture(enum Texture key);

GLuint load_shader(enum Shader key);

struct GLObject load_model(enum Model key);

int assets_init();

void assets_free();

#endif

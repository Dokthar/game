#include <GL/glew.h>
#include <stdlib.h>

#include "debug.h"
#include "assets.h"

#include "shader.h"
#include "texture.h"
#include "material.h"

static const char *const path_models[NB_MODELS] =
{
	"cube.obj",
	"tetrapod-concrete.obj",
};

static const char *const path_textures[NB_TEXTURES] =
{
	"null"
};

static const char *const path_vertex_shaders[NB_SHADERS] =
{
	"shaders/solid_color.vert",
};

static const char *const path_fragment_shaders[NB_SHADERS] =
{
	"shaders/solid_color.frag",
};


struct GLObject models[NB_MODELS] = {0};

GLuint textures[NB_TEXTURES] = {0};

GLuint shaders[NB_SHADERS] = {0};

struct GLObject load_model(enum Model key)
{
	return models[key];
}

GLuint load_texture(enum Texture key)
{
	return textures[key];
}

GLuint load_shader(enum Shader key)
{
	return shaders[key];
}


int models_init()
{
	unsigned int i;
	struct Mesh *mesh;
/* FIXME : free mesh ! */
	mesh = malloc(sizeof(struct Mesh));
	if (!mesh) {
		return 1;
	}

	for (i = 0; i < NB_MODELS; i++) {
		dbg_printf("models_init: [%d/%d] models/%s\n", i, NB_MODELS, path_models[i]);
		mesh_load(mesh, "models", path_models[i]);
		globject_new(mesh, &models[i]);
	}
	dbg_printf("models_init: [%d/%1$d] ... DONE\n", NB_MODELS);

	return 0;
}


int shaders_init()
{
	unsigned int i;

	for (i = 0; i < NB_SHADERS; i++) {
		dbg_printf("shader_init: [%d/%d] %s - %s\n", i, NB_SHADERS,
		           path_vertex_shaders[i], path_fragment_shaders[i]);
		shaders[i] = shader_compile(path_vertex_shaders[i],
				path_fragment_shaders[i]);
		if (!shaders[i]) {
			return 1;
		}
	}
	dbg_printf("shader_init: [%d/%1$d] ... DONE\n", NB_SHADERS);
	return 0;
}

int assets_init()
{
	int err;
/* FIXME : can't load shaders after models... this is supicious */
	err = shaders_init();
	if (err) {
		assets_free();
		return err;
	}

	err = models_init();
	if (err) {
		assets_free();
		return err;
	}
	return 0;
}

void assets_free()
{
	unsigned int i;

	for (i = 0; i < NB_MODELS; i++) {
		globject_free(&models[i]);
	}
	
	for (i = 0; i < NB_SHADERS; i++) {
		if (shaders[i])
			glDeleteProgram(shaders[i]);
		else
			break;
	}

	glDeleteTextures(NB_TEXTURES, textures);
}

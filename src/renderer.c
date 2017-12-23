#include "renderer.h"

#include "globject.h"
#include "camera.h"
#include "linear_algebra.h"
#include "material.h"

void render(const struct Camera *camera, const struct Geometry *geom)
{
	const struct Material *mat = geom->material;
	const struct GLObject *glo = geom->globject;
	const GLuint shader = mat->shader;

	glUseProgram(shader);
	glBindVertexArray(glo->vao);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, (float*)camera->projection);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, (float*)camera->view);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)*geom->transform);

	/* TODO: material specific render */
	glUniform3fv(glGetUniformLocation(shader, "solidColor"), 1, (float*)mat->diffuse);

	glDrawArrays(GL_TRIANGLES, 0, glo->numVertices);
	glUseProgram(0);
}



void render_text(const struct Camera *camera, const struct Geometry *geom, GLuint texture)
{
	const struct Material *mat = geom->material;
	const struct GLObject *glo = geom->globject;
	const GLuint shader = mat->shader;

	glUseProgram(shader);
	glBindVertexArray(glo->vao);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, (float*)camera->projection);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, (float*)camera->view);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)*geom->transform);

	/* TODO: material specific render */
	glUniform3fv(glGetUniformLocation(shader, "solidColor"), 1, (float*)mat->diffuse);
	glUniform1i(glGetUniformLocation(shader, "tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	/*glBindTexture(GL_TEXTURE_2D, texture);*/

	glDrawArrays(GL_TRIANGLES, 0, glo->numVertices);
	glUseProgram(0);
}

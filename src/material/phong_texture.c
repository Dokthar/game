#include "phong_texture.h"
#include "shaders.h"

void phong_texture_material_init(struct PhongTextureMaterial* phongtexture) {
    struct Material* mat = &phongtexture->mat;

    material_init(mat, "phong texture", 5, &phongtexture->ambient);
    mat->shader = game_shaders[SHADER_PHONG_TEXTURE];

    phongtexture->ambient.name = "phong.ambient";
    phongtexture->diffuse.name = "phong.diffuse";
    phongtexture->specular.name = "phong.specular";
    phongtexture->shininess.name = "phong.shininess";
    phongtexture->texture.name = "tex";

    material_set_color(mat, "phong.ambient", 1, 1, 1);
    material_set_color(mat, "phong.diffuse", 1, 1, 1);
    material_set_color(mat, "phong.specular", 1, 1, 1);
    material_set_float(mat, "phong.shininess", 1);
    material_set_texture(mat, "tex", 0);
}

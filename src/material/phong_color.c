#include "solid_color.h"
#include "phong_color.h"
#include "shaders.h"

void phong_color_material_init(struct PhongColorMaterial* phongcolor) {
    struct Material* mat = &phongcolor->mat;

    material_init(mat, "phong color", 5, &phongcolor->ambient);
    mat->shader = game_shaders[SHADER_PHONG_COLOR];

    phongcolor->ambient.name = "phong.ambient";
    phongcolor->diffuse.name = "phong.diffuse";
    phongcolor->specular.name = "phong.specular";
    phongcolor->shininess.name = "phong.shininess";
    phongcolor->color.name = "color";

    material_set_color(mat, "phong.ambient", 1, 1, 1);
    material_set_color(mat, "phong.diffuse", 1, 1, 1);
    material_set_color(mat, "phong.specular", 1, 1, 1);
    material_set_float(mat, "phong.shininess", 1);
    material_set_color(mat, "color", 0, 0, 0);
}

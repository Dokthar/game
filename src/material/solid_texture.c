#include "solid_texture.h"
#include "shaders.h"

void solid_texture_material_init(struct SolidTextureMaterial* solidtexture) {
    struct Material* mat = &solidtexture->mat;

    material_init(mat, "solid texture", 1, &solidtexture->texture);
    mat->shader = game_shaders[SHADER_SOLID_TEXTURE];

    solidtexture->texture.type = TEXTURE;
    solidtexture->texture.name = "texture1";
    matparam_set_texture(&solidtexture->texture, 0);
}

#version 130

#include "phong.glsl"

in vec3 surfelPosition;
in vec3 surfelNormal;
out vec4 out_Color;

uniform vec3 cameraPosition;
uniform vec3 color;

void main() {
    out_Color = vec4(color, 1) * vec4(phong_light_factor(cameraPosition, surfelPosition, surfelNormal), 1.0);
}

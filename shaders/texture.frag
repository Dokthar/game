#version 130

in vec2 coordTexture;
in vec4 color;

uniform sampler2D tex;

out vec4 out_Color;


void main()
{
    out_Color = texture(tex, coordTexture);
}
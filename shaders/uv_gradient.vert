#version 130

in vec3 in_Vertex;
in vec3 in_Normal;
in vec2 in_TexCoord;

out vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 solidColor;

void main()
{
    gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    color = vec4(solidColor * in_TexCoord.x
          + vec3(0.1333, 0.1333, 0.1333) * in_TexCoord.y
          + vec3(0.0) * (1 - in_TexCoord.x - in_TexCoord.y), 1.0);
}

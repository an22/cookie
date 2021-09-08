#version 410

out vec4 color;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

in vec2 _texCoord;
in vec4 varyingColor;

uniform sampler2D diffuse1;
uniform sampler2D specular1;

void main(void) {
    color = varyingColor;
}

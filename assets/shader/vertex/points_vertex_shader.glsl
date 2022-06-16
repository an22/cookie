#version 410

precision highp float;
precision highp int;

layout (location=0) in vec4 position;

layout (binding = 0, std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
} matrixData;

out vec4 color;

void main(void) {
    color = position;
    gl_Position = matrixData.projection * matrixData.view * position;
}
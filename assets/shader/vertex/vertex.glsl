#version 410

precision highp float;
precision highp int;

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;
layout (location=3) in int matrixOffset;

layout (binding = 0, std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
} matrixData;

layout (binding = 1, std140) buffer ModelMatrices
{
    mat4[] data;
} modelMatrices;

uniform samplerBuffer matrixBuffer;
out vec2 lerpTexCoord;
out vec4 color;

mat4 findMatrix(int offset);

void main(void) {
    mat4 mv_matrix = matrixData.view * modelMatrices.data[matrixOffset];
    color = vec4(normal, 1.0f);
    gl_Position = matrixData.projection * mv_matrix * vec4(position, 1.0);
    lerpTexCoord = texCoord;
}
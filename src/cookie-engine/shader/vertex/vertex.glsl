#version 410

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;
layout (location=3) in int matrixOffset;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
} matrixData;

uniform samplerBuffer matrixBuffer;

mat4 findMatrix(int offset);

void main(void) {
    mat4 mv_matrix = matrixData.view * findMatrix(matrixOffset);
    gl_Position = matrixData.projection * mv_matrix * vec4(position, 1.0);
}

mat4 findMatrix(int offset)
{
    return mat4(
    texelFetch(matrixBuffer, offset * 4),
    texelFetch(matrixBuffer, offset * 4 + 1),
    texelFetch(matrixBuffer, offset * 4 + 2),
    texelFetch(matrixBuffer, offset * 4 + 3)
    );
}

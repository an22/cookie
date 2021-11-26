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

out vec4 varyingColor;

mat4 findMatrix(int offset);

void main(void) {
    mat4 mv_matrix = matrixData.view * mat4(1.0);
    gl_Position = matrixData.projection * mv_matrix * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
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

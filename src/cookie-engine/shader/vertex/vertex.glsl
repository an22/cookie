#version 410

struct Material {
    vec2 diff;
};

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;
layout (location=3) in uint matrixOffset;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
} matrixData;

uniform samplerBuffer matrixBuffer;

uniform materialBuffer {
    Material materials;
};

in ivec2 vAssigns;
flat out ivec2 fAssigns;

mat4 findMatrix(int offset)
{
    return mat4(
        texelFetch(matrixBuffer, offset),
        texelFetch(matrixBuffer, offset + 1),
        texelFetch(matrixBuffer, offset + 2),
        texelFetch(matrixBuffer, offset + 3)
    );
}

void main(void) {
    gl_Position = matrixData.projection * matrixData.view * findMatrix(matrixOffset) * vec4(position, 1.0);
}

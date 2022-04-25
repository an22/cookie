#version 320 es

precision mediump float;

out vec4 color;
layout (shared) uniform Material
{
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambientColor;
    vec3 emissiveColor;
    vec3 transparencyColor;

    float opacity;
    float shininess;
    float refraction;
} material;

layout(binding = 0) uniform sampler2D diffuseTxr;
in vec2 lerpTexCoord;

void main(void) {
    color = texture(diffuseTxr, lerpTexCoord);
}

#version 410

precision highp float;

out vec4 color;
layout (shared) uniform Material
{
    vec4 baseColor;
    vec4 emissiveColor;
    float roughness;
    float metallic;
    float specular;
    float opacity;
    float shininess;
    int doubleSided;
} material;

in vec2 lerpTexCoord;

void main(void) {
    color = vec4(0.8,0.8,0.8,1);
}

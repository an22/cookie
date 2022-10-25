#version 430

precision highp float;

out vec4 color1;
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
in vec4 color;

void main(void) {
    color1 = vec4(0.5 * normalize(color.rgb) + 0.5, 1.0);
}

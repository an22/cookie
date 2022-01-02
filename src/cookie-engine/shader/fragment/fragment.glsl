#version 410

out vec4 color;
layout (binding = 1) uniform Material
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

void main(void) {
    color = vec4(material.diffuseColor, 1.0);
}

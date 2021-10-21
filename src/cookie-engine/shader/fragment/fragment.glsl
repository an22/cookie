#version 410

out vec4 color;

struct Material {
    vec2 diff;
};

uniform materialBuffer {
    Material materials;
};

in ivec2 fAssigns;

void main(void) {
    color = vec4(0.0f, 0.0f, 0.0f, 1f);
}

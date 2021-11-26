#version 410

out vec4 color;
in vec4 varyingColor;

void main(void) {
    color = varyingColor;
}

#version 430

precision highp float;

out vec4 color1;
in vec4 color;

void main(void) {
    color1 = vec4(0.5 * normalize(color.rgb) + 0.5, 1.0);
}
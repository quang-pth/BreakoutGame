#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;
in vec4 Color;

uniform sampler2D image;

void main() {
    FragColor = texture(image, TexCoords) * Color;
}
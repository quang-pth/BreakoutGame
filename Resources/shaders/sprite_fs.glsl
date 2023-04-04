#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D sprite;

void main() {
    FragColor = texture(sprite, TexCoords);
}
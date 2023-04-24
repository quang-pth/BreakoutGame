#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D text;
uniform vec3 Color;

void main() {
    FragColor = vec4(Color, texture(text, TexCoords).r);
}
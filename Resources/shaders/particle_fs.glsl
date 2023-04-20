#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoords;

uniform vec3 Color;
uniform float Alpha;
uniform sampler2D image;

void main() {
    FragColor = texture(image, TexCoords) * vec4(Color, Alpha);
}
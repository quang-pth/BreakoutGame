#version 330 core

layout (location = 0) out vec4 FragColor;

in vec3 Position;
in vec4 Color;

void main() {
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // FragColor = vec4(Position, 1.0);
}
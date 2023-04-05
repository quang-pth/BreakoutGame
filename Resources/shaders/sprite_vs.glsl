#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec3 Position;
out vec2 TexCoords;

uniform mat4 Transform;
uniform mat4 Projection;

void main() {
    TexCoords = aTexCoords;
    Position = aPosition;

    gl_Position = vec4(aPosition, 1.0f) * Transform * Projection;
}
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 Projection;
uniform mat4 Transform;

void main() {
    TexCoords = aTexCoords;

    gl_Position = vec4(aPosition.x, aPosition.y, 0.0f, 0.0f) * Transform * Projection;
}
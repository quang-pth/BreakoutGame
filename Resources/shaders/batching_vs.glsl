#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 Color;
out vec3 Position;

uniform mat4 simpleViewProjection;

void main() {
    gl_Position = vec4(aPosition, 1.0) * simpleViewProjection;
    Color = aColor;
    Position = aPosition;
}
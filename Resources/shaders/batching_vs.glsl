#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

out vec4 Color;

uniform mat4 orthoProj;

void main() {
    Color = aColor;
    gl_Position = vec4(aPosition, 1.0) * orthoProj;
}
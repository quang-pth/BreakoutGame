#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 Projection;
uniform mat4 Transform;
uniform vec2 offset;

void main() {
    TexCoords = aTexCoords;

    float scale = 10.0f;
    gl_Position = vec4(aPosition.xy * scale + offset, 0.0f, 1.0f) * Transform * Projection; 
}

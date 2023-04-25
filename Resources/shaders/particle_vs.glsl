#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in mat4 aTransforms;
layout (location = 6) in vec4 aColor;

out vec2 TexCoords;
out vec4 Color;
out float Alpha;

uniform mat4 Projection;
uniform vec2 offset;

void main() {
    TexCoords = aTexCoords;
    Color = aColor;

    float scale = 10.0f;
    gl_Position = vec4(aPosition.xy * scale + offset, 0.0f, 1.0f) * transpose(aTransforms) * Projection; 
}

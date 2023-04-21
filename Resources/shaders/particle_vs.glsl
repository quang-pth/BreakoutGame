#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Color;
out float Alpha;

uniform mat4 Transforms[100];
uniform vec3 Colors[100];
uniform float Alphas[100];
uniform mat4 Projection;
uniform vec2 offset;

void main() {
    TexCoords = aTexCoords;
    Color = Colors[gl_InstanceID];
    Alpha = Alphas[gl_InstanceID];

    float scale = 10.0f;
    gl_Position = vec4(aPosition.xy * scale + offset, 0.0f, 1.0f) * Transforms[gl_InstanceID] * Projection; 
}

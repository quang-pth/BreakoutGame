#version 330 core 

layout (location = 0) in vec4 aVertex;

out vec2 TexCoords;

uniform mat4 Projection;

void main() {
    gl_Position = vec4(aVertex.xy, 0.0f, 1.0f) * Projection;

    TexCoords = aVertex.zw;
}
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform bool chaos;
uniform bool confuse;
uniform bool shake;
uniform float time;

void main() {
    TexCoords = aTexCoords;
    gl_Position = vec4(aPosition, 1.0);

    if (chaos) {
        float strength = 0.3;
        TexCoords = vec2(aTexCoords.x + sin(time) * strength, aTexCoords.y + cos(time) * strength);
    }
    else if (confuse) {
        TexCoords = vec2(1.0 - aTexCoords.x, 1.0 - aTexCoords.y);
    }

    if (shake) {
        float strength = 0.01;
        gl_Position.x += cos(time * 10) * strength;
        gl_Position.y += sin(time * 15) * strength;
    }
}

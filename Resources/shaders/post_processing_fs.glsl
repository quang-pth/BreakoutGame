#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

#define N 9

uniform sampler2D scene;
uniform vec2 offsets[N];
uniform int edgeKernel[N];
uniform float blurKernel[N];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

void main() {
    FragColor = vec4(0.0);
    vec3 sample[N];

    if (chaos || shake) {
        for (int i = 0; i < N; i++) {
            sample[i] = vec3(texture(scene, TexCoords.st + offsets[i]));
        }
    }

    if (chaos) {
        for (int i = 0; i < N; i++) {
            FragColor += vec4(sample[i] * edgeKernel[i], 0.0);
        }
        FragColor.a = 1.0;
    }
    else if (confuse) {
        FragColor = vec4(1.0 - texture(scene, TexCoords).rgb, 1.0);
    }
    else if (shake) {
        for (int i = 0; i < N; i++) {
            FragColor += vec4(sample[i] * blurKernel[i], 0.0);
        }
        FragColor.a = 1.0;
    }
    else {
        FragColor = texture(scene, TexCoords);
    }
}
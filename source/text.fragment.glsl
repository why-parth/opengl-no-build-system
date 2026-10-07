#version 460 core

in vec2 texCoord;
out vec4 color;

uniform sampler2D aTexture;
uniform vec3 texColor;

void main () {

    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(aTexture, texCoord).r);

    color = vec4(texColor, 1.0) * sampled;

}
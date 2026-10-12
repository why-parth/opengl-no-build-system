#version 460 core
layout (location = 0) in vec2 aPos;

uniform mat4 transform;

void main(void) {

    gl_Position = transform * vec4(aPos, 0, 1);

}
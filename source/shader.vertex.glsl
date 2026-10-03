#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

out vec3 Col;
out vec2 Tex;
out vec2 Pos;

uniform mat4 transform;

void main () {

    Col = aCol;
    Tex = aTex;

    gl_Position = transform * vec4(aPos.x, aPos.y, 0.0, 1.0);
    
    Pos = gl_Position.xy;
    
}
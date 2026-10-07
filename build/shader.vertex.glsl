#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTex;

out vec3 Col;
out vec2 Tex;
out vec2 Pos;

uniform mat4 transform;

uniform float trace;

uniform int mode;

void main () {

    Col = aCol;
    Tex = aTex;

    if (mode == 1) {
    gl_Position = transform * vec4(aPos.x + trace, aPos.y + trace, 0.0, 1.0);
    
    }
    else if (mode == 0) {
       gl_Position = vec4(aPos.x/4 + 0.8, aPos.y/4 + 0.8, 0.0, 1.0);
    }

    
    Pos = gl_Position.xy;
     
}
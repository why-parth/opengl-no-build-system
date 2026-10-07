#version 460 core

out vec4 FragColor;

in vec3 Col;
in vec2 Tex;
in vec2 Pos;

uniform vec2 mp;

uniform sampler2D image;

uniform int mode;

void main () {

    float i = distance(mp, Pos);
    
    if (mode == 1) {

    FragColor = clamp(texture(image, Tex) / (i*i + 0.1), 0, 1);

    }

    else if (mode == 0) {

    FragColor = vec4(Col, 1.0);

    }

}
#include "include/glh/window.hpp"
#include "include/glh/shader.hpp"
#include "include/glh/buffer.hpp"
#include "include/ft/ft2build.h"
#include FT_FREETYPE_H


// Debug

int __log__ = 1;

// Data

std::vector<VD_t> tri = {

     0.4,  0.4,  1.0, 0.0, 0.0, 1.0, 1.0,
    -0.4,  0.4,  1.0, 1.0, 0.0, 0.0, 1.0,
    -0.4, -0.4,  0.0, 1.0, 0.0, 0.0, 0.0,
     0.4, -0.4,  0.0, 0.0, 1.0, 1.0, 0.0

};

std::vector<GLuint> ind = {
    0, 1, 2,
    0, 3, 2
};

std::vector<VD_t> texture = {
    1.0, 1.0,
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0
};


int main (void) {

    FT_Library ft;
    FT_Init_FreeType(&ft);

    // Window

    Window(win);

    // Shader Setup

    Shader vrt(".\\shader.vertex.glsl");
    vrt % "vertex";

    Shader frg(".\\shader.fragment.glsl");
    frg % "fragment";

    Program program;
    program << vrt << frg;

    // Buffer Setup

    VertexData VBO;
    VBO << tri;
    VBO % 7;

    VertexData TEX;
    TEX << texture;
    TEX % 2;

    TextureData text;
    text << "Bricks_Color.jpg";
    text >> 2;

    TextureData wood;
    wood << "Wood_Color.jpg";
    wood >> 1;
    
    IndexData EBO;
    EBO << ind;

    // VAO setup
    
    AttributeData VAO;

    VAO(VBO, 7);
    VAO[0] = 2 , VBO;
    VAO[1] = 3 , VBO;

    VAO(TEX, 2);
    VAO[2] = 2 , VBO;

    VAO = 3 , EBO;

    // Uniform Setup

    program == "image";
    program.setUniform(1);

    glm::mat4 transform; // Tranformation Matrix
    GLint uniform_transform = program.locateUniform("transform");
    GLfloat t;

    GLuint uniform_mp = program.locateUniform("mp");

    // Frame Loop

    win frame {

        program == uniform_mp;
        program.setUniform(win.mouse_npos.x, win.mouse_npos.y);

        program == uniform_transform;
        t = glfwGetTime();
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.1f, -0.2f, 0.0f)); // Translates
        transform = glm::rotate(transform, glm::sin(t), glm::vec3(0.0, 0.0, 1.0)); // Rotation;
        program.setUniform(transform);

        VAO.drawIndex(0, 2);

    };

    // Termination

    std::putchar('\n');
    SUCCbi "Exited Succesfully!" STYLEnone;
    return 0;
}
#include "include/glh/window.hpp"
#include "include/glh/interactive.hpp"
#include "include/glh/buffer.hpp"



// Debug

int __log__ = 1;

// Data

std::vector<VD_t> tri = {

     0.4f,  0.4f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
    -0.4f,  0.4f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, 
    -0.4f, -0.4f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 
     0.4f, -0.4f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, 

     1.0f,  1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.0f,  1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    -1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
     1.0f, -1.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f

};

std::vector<GLuint> ind = {
    0, 1, 2,
    0, 3, 2,
    4, 5, 6,
    4, 7, 6
};


std::vector<VD_t> texture = {
    1.0, 1.0,
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0
};


void FUNC (void) {
    std::cout << "\nButton!";
}


int main (void) {
    // Window  //----\---------------/-----\--------------------------/------------ ---  --    -
    Window(win);

    // Shader Setup //------\----------/----------------\-------------------/------------ ---  --    -
    int i = 1;
    Shader vrt(".\\shader.vertex.glsl"); vrt % "vertex";
    Shader frg(".\\shader.fragment.glsl"); frg % "fragment";
    Program program;
    program << vrt << frg << win;

    Shader inter_vrt(".\\inter.vertex.glsl"); inter_vrt % "vertex";
    Shader inter_frg(".\\inter.fragment.glsl"); inter_frg % "fragment";
    Program inter_program;
    inter_program << inter_vrt << inter_frg << win;
    
    Shader text_vrt(".\\text.vertex.glsl"); text_vrt % "vertex";
    Shader text_frg(".\\text.fragment.glsl"); text_frg % "fragment";
    Program textRenderer;
    textRenderer << text_vrt << text_frg << win;

    // Buffer Setup //-----------\----------/-----------\-------------/--------\-------------------/--- ---  --    -
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
    EBO % 3;

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

    // Font 

    TextureData Arial;
    Arial >> 4;
    Arial.font("Arial.ttf");

    TextureData EBGaramond;
    EBGaramond >> 5;
    EBGaramond.font("EBGaramond.ttf");

    TextureData Montserrat;
    Montserrat >> 5;
    Montserrat.font("Montserrat.ttf");

    textRenderer.font(Montserrat);

    // Frame Loop

    // Interactive TR(inter_program, {1000, 800}, {150, 50}, glm::vec2{1, 1});

    Interactive button(inter_program);

    button.position = {0, 800};
    button.size = {200, 50};
    button.center = {0, 1};
    button.active_press_function = FUNC;

    PRESET_BUTTON_GENERIC(button);

    button.init();


    win frame {

        program == uniform_mp;
        program.setUniform(win.mouse_npos.x, win.mouse_npos.y);

        program == uniform_transform;
        t = glfwGetTime();
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(0.1f, -0.2f, 0.0f)); // Translates
        transform = glm::rotate(transform, glm::sin(t), glm::vec3(0.0, 0.0, 1.0)); // Rotation;
        program.setUniform(transform);

        program == "trace";
        program.setUniform((glm::cos(2*t) + glm::sin(3*t))/10);

        program == "mode";
        program.setUniform(1);
        VAO.drawIndex(0, 2);

        program.setUniform(0);
        VAO.drawIndex(0, 2);

        textRenderer.font(Montserrat);
        textRenderer.text("This text is moving!", 100 + glm::cos(2*t) * 50, 100 + glm::sin(4*t) * 10, 0.5f, glm::vec3(250, 200, 150));
        
        textRenderer.font(EBGaramond);
        textRenderer.text("OpenGL", 50, 600, 1.0f, glm::vec3(win.fore));

        button.display();

    };

    // Termination

    std::putchar('\n');
    SUCCbi "Exited Succesfully!" STYLEnone;
    return 0;
}
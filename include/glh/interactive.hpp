#ifndef GLH_Interactive_Header
#define GLH_Interactive_Header

#include "include/glh/shader.hpp"

#define PRESET_BUTTON_GENERIC(_Name)                    \
_Name.color = glm::vec4(0.15, 0.22, 0.18, 0.5);         \
_Name.hover_color = glm::vec4(0.3, 0.4, 0.4, 0.7);      \
_Name.active_color = glm::vec4(0.2, 0.3, 0.3, 1.0)


class Interactive {

    public:

    int __log__ = 1;

    glm::vec2 position;
    glm::vec2 size;
    glm::vec2 center;

    glm::vec4 color;
    glm::vec4 active_color;
    glm::vec4 hover_color;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    glm::vec4 rect; 

    void (* active_press_function)(void) = NULL;
    void (* active_release_function)(void) = NULL;
    GLint active_function_called = 0;

    Program renderer;
    
    Interactive(Program _Renderer) {

        this->renderer = _Renderer;

    }

    void init(void) {
        
        glm::vec2 position = glm::vec2(2 * this->position.x / this->renderer.window->width - 1, 2 * this->position.y / this->renderer.window->height - 1);
        glm::vec2 size = glm::vec2(2 * this->size.x / this->renderer.window->width, 2 * this->size.y / this->renderer.window->height);
        glm::vec2 center = this->center;

        GLfloat vertex_data[] = {
            position.x - size.x * center.x,          position.y - size.y * center.y,
            position.x + size.x * (1 - center.x),    position.y - size.y * center.y,
            position.x + size.x * (1 - center.x),    position.y + size.y * (1 - center.y),
            position.x - size.x * center.x,          position.y + size.y * (1 - center.y),
        };

        this->rect = glm::vec4(vertex_data[0], vertex_data[1], vertex_data[4], vertex_data[5]);

        GLuint index_data[] = {
            0, 1, 2,
            0, 3, 2
        };

        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);

        glBindVertexArray(vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 2, NULL);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

        glBindVertexArray(0);

    }

    void display(void) {

        if (
            this->renderer.window->mouse_npos.x >= this->rect[0]
            && 
            this->renderer.window->mouse_npos.x <= this->rect[2]
            && 
            this->renderer.window->mouse_npos.y >= this->rect[1]
            && 
            this->renderer.window->mouse_npos.y <= this->rect[3]
        ) {
            this->renderer.locateUniform("color");

            if (this->renderer.window->mouse_left) {
                this->renderer.setUniform(this->active_color.r, this->active_color.g, this->active_color.b, this->active_color.a);\
                if (!active_function_called || active_function_called == 2) if (active_press_function) {
                    active_press_function();
                    active_function_called = 1;
                }
            }

            else {
                this->renderer.setUniform(this->hover_color.r, this->hover_color.g, this->hover_color.b, this->hover_color.a);
                if (active_function_called == 1) active_function_called = 2;
            }

        }

        else {
            this->renderer.locateUniform("color");
            this->renderer.setUniform(this->color.r, this->color.g, this->color.b, this->color.a);
            if (active_function_called == 2) active_function_called = 0;
        }

        this->renderer.use();
        glBindVertexArray(this->vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    }

};

#endif
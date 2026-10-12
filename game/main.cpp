#include "include/glh/window.hpp"
#include "include/glh/interactive.hpp"
#include "include/glh/buffer.hpp"

#define WIN_W   1000
#define WIN_H   800
#define WIN_FPS 60
#define PIXEL_METER_RATIO 1
#define mpr * glm::vec2(1.0f / PIXEL_METER_RATIO)

// Debug

int __log__ = 1;

// Data

// GLfloat ground_noramalised_function(GLfloat x) {
//     return -0.9;
// } 

glm::vec2 player_position = {200, 200};
glm::vec2 player_velocity = {0, 0};
glm::vec2 player_accelaration = {0, 0};
glm::vec2 player_shape = {100, 100};
glm::vec2 player_size = {1, 1};
GLfloat player_rotation = 0.0f;
glm::mat4 player_transform;
GLfloat player_jump = 60;
GLfloat player_rotation_speed = 0.4;
GLint player_colision = 0;
GLint player_face_x = 0;
GLfloat player_speed = 40;
GLint player_move_dir = 0;

void player_gen(Program _Program) {
    glm::vec2 position = ( glm::vec2(2, 2) * player_position / glm::vec2(WIN_W, WIN_H) ) - glm::vec2(1, 1);
    glm::vec2 scale = ( (glm::vec2(2, 2) * player_size * player_shape) / glm::vec2(WIN_W, WIN_H) );
    player_transform = glm::mat4(1);

    player_transform = glm::translate(player_transform, glm::vec3(position, 0.0f));
    player_transform = glm::scale(player_transform, glm::vec3(scale, 0.0f));
    player_transform = glm::rotate(player_transform, glm::radians(player_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    _Program == "transform";
    _Program.setUniform(player_transform);
}

void player_gravity(void) {
    glm::vec2 scale;

    if (!player_colision) {
        player_position += (player_velocity / glm::vec2(WIN_FPS) + player_accelaration / (glm::vec2(2 * WIN_FPS) * glm::vec2(WIN_FPS))) mpr;
        player_velocity += (player_accelaration / glm::vec2(WIN_FPS)) mpr;

        GLfloat height = 0;
        scale = player_size * player_shape;

        if (player_position.y < (player_face_x ? scale.x : scale.y) ) player_colision = -1;
    }
    
    if (player_colision == -1) {
        player_position.y = (player_face_x ? scale.x : scale.y);
        player_colision = 0;
    }
}



int main (void) {
    // Window  //----\---------------/-----\--------------------------/------------ ---  --    -
    Window win (WIN_W, WIN_H, "Game");
    win.FPS = WIN_FPS;

    // Shader Setup //------\----------/----------------\-------------------/------------ ---  --    -
    Shader player_vertex_shader("player.vertex.glsl"); player_vertex_shader % "vertex"; 
    Shader player_fragment_shader("player.fragment.glsl"); player_fragment_shader % "fragment"; 
    Program player_program;
    player_program << player_vertex_shader;
    player_program << player_fragment_shader;
    player_program << win;

    // Buffer Setup //-----------\----------/-----------\-------------/--------\-------------------/--- ---  --    -
    std::vector<GLfloat> player_vertex_data {
        -1.0,  1.0,     1.0,  1.0,
        -1.0, -1.0,     1.0, -1.0
    };

    VertexData player_VBO;
    player_VBO << player_vertex_data;
    player_VBO % 2;

    std::vector<GLuint> player_index_data {
        0, 1, 2,
        1, 2, 3
    };

    IndexData player_EBO;
    player_EBO << player_index_data;
    player_EBO % 3;

    // VAO setup

    AttributeData player_VAO;

    player_VAO(player_VBO, 2);
    player_VAO[0] = 2, player_VBO;
    player_VAO = 3, player_EBO;

    // Uniform Setup


    // Font 


    // Frame Loop
    int press;
    int jump = 0;
    player_accelaration.y = -10;
    float player_do_rotation = 0;
    float player_prev_move_dir;


    win frame {

        press = glfwGetKey(win.object, GLFW_KEY_SPACE);
        if (!jump && press == GLFW_PRESS) jump = 1;
        else if (press == GLFW_RELEASE) jump = 0;

        press = glfwGetKey(win.object, GLFW_KEY_RIGHT);
        if (press == GLFW_PRESS) {
            player_velocity.x = player_speed;
            player_prev_move_dir = player_move_dir;
            player_move_dir = 1;
        }
        else if (player_move_dir == 1 && press == GLFW_RELEASE) {
            player_velocity.x = 0;
            player_prev_move_dir = player_move_dir;
            player_move_dir = 0;
        }

        press = glfwGetKey(win.object, GLFW_KEY_LEFT);
        if (press == GLFW_PRESS) {
            player_velocity.x = -player_speed;
            player_prev_move_dir = player_move_dir;
            player_move_dir = -1;
        }
        else if (player_move_dir == -1 && press == GLFW_RELEASE) {
            player_velocity.x = 0;
            player_prev_move_dir = player_move_dir;
            player_move_dir = 0;
        }


        if (jump == 1) {
            jump = 2;
            player_velocity.y = player_jump;
            if (player_move_dir) {
                if (player_move_dir)
                if ((!player_prev_move_dir) || player_move_dir == player_prev_move_dir) player_do_rotation = 90;
                else {
                    player_do_rotation = 180 - player_do_rotation;
                }
                player_face_x = !player_face_x;
            }
        } 

        if (player_do_rotation != 0) {
            player_rotation -= player_move_dir * player_rotation_speed;
            player_do_rotation -= player_rotation_speed;
            if (player_do_rotation < 0) {
                player_rotation += player_do_rotation;
                player_do_rotation = 0;
            }
        }

        // player_rotation += 0.1;

        player_gravity();

        player_gen(player_program);
        player_VAO.drawIndex(0, 2);

    };

    // Termination

    std::putchar('\n');
    SUCCbi "Exited Succesfully!" STYLEnone;
    return 0;
}


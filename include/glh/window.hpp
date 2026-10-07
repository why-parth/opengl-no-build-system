#ifndef GLH_Window_Header
#define GLH_Window_Header

/*
This header manages :-
- Initialization of GLFW and GLAD
- Creation of Window
- The code that runs in a window per frame can be defined as
    window_name frame {
        // Code
    }
- Swapping the buffer and default screen clearing runs. Window closing is also handled.
- Event handling is not handled.
*/

#include "include/glh/base.hpp"
 
#define frame << [&] (Window& This)

class WindowUtils;

class Window {
    
    public:
    static GLint glfwInitialized;
    static GLint gladInitialized;
    GLint exit_window = 0;
    GLint __log__ = 1;

    GLFWwindow * object = NULL;
    std::string title = "Unnamed";
    GLint width;
    GLint height;
    glm::dvec2 mouse_pos;
    glm::vec2 mouse_npos;

    glm::vec4 back = {28.0f, 34.0f, 32.0f, 1.0f} ;
    glm::vec4 fore = {255.0f, 255.0f, 255.0f, 1.0f} ;

    Window (unsigned int width = 1000, unsigned int height = 800, char * title = NULL);
    ~Window (void);

    void loop(std::function<void(Window& This)>);
    void operator<<(std::function<void(Window& This)> _Code);

    void color(double _GrayValue);
    void color(double _GrayValue, double _Alpha);
    void color(double _Red, double _Green, double _Blue);
    void color(double _Red, double _Green, double _Blue, double _Alpha);

    void draw_color(double _GrayValue);
    void draw_color(double _GrayValue, double _Alpha);
    void draw_color(double _Red, double _Green, double _Blue);
    void draw_color(double _Red, double _Green, double _Blue, double _Alpha);

    void fill(double _GrayValue);
    void fill(double _GrayValue, double _Alpha);
    void fill(double _Red, double _Green, double _Blue);
    void fill(double _Red, double _Green, double _Blue, double _Alpha);
    void fill(void);

};

class WindowUtils {
    
    public:
    static void FrameBufferSize_CallBack(GLFWwindow * _Window, int _Width, int _Height);

};

#endif
#ifndef GLH_Window_Header
#define GLH_Window_Header

#include "include/glh/draw.hpp"
 
#define frame << [&] (Window& This)

typedef struct { double r, g, b, a; } Color;

class WindowUtils;

class Window : virtual public Drawer {

    static int glfwInitialized;
    static int gladInitialized;
    int exit_window = 0;
    
    public:
    int __log__ = 1;


    GLFWwindow * object = NULL;
    std::string title = "Unnamed";
    GLint width;
    GLint height;
    struct { GLdouble x, y; } mouse_pos;
    struct { GLfloat x, y; } mouse_npos;

    
    Color back = {28.0f, 34.0f, 32.0f, 1.0f} ;
    Color fore = {255.0f, 255.0f, 255.0f, 1.0f} ;

    
    Window (unsigned int width = 1000, unsigned int height = 800, char * title = NULL);
    ~Window (void);

    void loop(std::function<void(Window& This)>);
    void operator<<(std::function<void(Window& This)> _Code);


    void color(double _GrayValue);
    void color(double _GrayValue, double _Alpha);
    void color(double _Red, double _Green, double _Blue);
    void color(double _Red, double _Green, double _Blue, double _Alpha);

    void fore_color(double _GrayValue);
    void fore_color(double _GrayValue, double _Alpha);
    void fore_color(double _Red, double _Green, double _Blue);
    void fore_color(double _Red, double _Green, double _Blue, double _Alpha);

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
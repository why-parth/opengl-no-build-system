#include "include/glh/window.hpp"


int Window::glfwInitialized = 0;
int Window::gladInitialized = 0;


Window::Window (unsigned int width, unsigned int height, char * title) {
    if (!glfwInitialized) {
        glfwInitialized = 1;
        if (!glfwInit()) {
            ERR "GLFW could not be initialized!";
            exit(-1);
        }
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        LOG "GLFW initialized.";
    }
    
    title = (char *)this->title.c_str();
    this->width = width;
    this->height = height;
    this->object = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!this->object) {
        ERR "Window '" __NAME__(title) "' could not be created!";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(this->object);

    if (!gladInitialized) {
        gladInitialized = 1;
        if (!gladLoadGL(glfwGetProcAddress)) {
            ERR "GLAD could not be initialized!";
            glfwDestroyWindow(this->object);
            glfwTerminate();
            exit(-1);
        }
        LOG "GLAD initialized.";
    }
    
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(this->object, WindowUtils::FrameBufferSize_CallBack);

    glfwGetCursorPos(this->object, &this->mouse_pos.x, &this->mouse_pos.y);

    LOG "Window '" __NAME__(title) "' created.";
    
}


Window::~Window (void) {
    glfwDestroyWindow(this->object);
    glfwTerminate();
}


void Window::loop(std::function<void(Window& This)> _Code) {
    while (!exit_window) {
        if (glfwWindowShouldClose(this->object)) {
            this->exit_window = 1;
            break;
        }

        glfwGetFramebufferSize(this->object, &this->width, &this->height);
        glfwGetCursorPos(this->object, &this->mouse_pos.x, &this->mouse_pos.y);
        this->mouse_pos.y = this->height - this->mouse_pos.y;
        this->mouse_npos.x = 2 * this->mouse_pos.x/this->width - 1;
        this->mouse_npos.y = 2 * this->mouse_pos.y/this->height - 1;

        if (this->mouse_pos.x >= this->width) this->mouse_pos.x = this->width - 1;
        else if (this->mouse_pos.x < 0) this->mouse_pos.x = 0;

        if (this->mouse_pos.y >= this->height) this->mouse_pos.y = this->height - 1;
        else if (this->mouse_pos.y < 0) this->mouse_pos.y = 0;

        this->fill();

        _Code(*this);

        glfwPollEvents();
        glfwSwapBuffers(this->object);
    }
}


void Window::operator << (std::function<void(Window& This)> _Code) {
        this->loop(_Code);
    }


void Window::color(double _GrayValue)
    { this->back.r = this->back.g = this->back.b =_GrayValue, this->back.a = 1.0f; }
void Window::color(double _GrayValue, double _Alpha)
    { this->back.r = this->back.g = this->back.b = _GrayValue, this->back.a = _Alpha; }
void Window::color(double _Red, double _Green, double _Blue)
    { this->back.r = _Red; this->back.g = _Green;  this->back.b =_Blue; this->back.a = 1.0f; }
void Window::color(double _Red, double _Green, double _Blue, double _Alpha)
    { this->back.r = _Red; this->back.g = _Green;  this->back.b =_Blue; this->back.a = _Alpha; }

void Window::fore_color(double _GrayValue)
    { this->fore.r = this->fore.g = this->fore.b =_GrayValue, this->fore.a = 1.0f; }
void Window::fore_color(double _GrayValue, double _Alpha)
    { this->fore.r = this->fore.g = this->fore.b = _GrayValue, this->fore.a = _Alpha; }
void Window::fore_color(double _Red, double _Green, double _Blue)
    { this->fore.r = _Red; this->fore.g = _Green;  this->fore.b =_Blue; this->fore.a = 1.0f; }
void Window::fore_color(double _Red, double _Green, double _Blue, double _Alpha)
    { this->fore.r = _Red; this->fore.g = _Green;  this->fore.b =_Blue; this->fore.a = _Alpha; }

void Window::fill(double _GrayValue)
    { glClearColor(_GrayValue/255.0f, _GrayValue/255.0f, _GrayValue/255.0f, 1); }
void Window::fill(double _GrayValue, double _Alpha)
    { glClearColor(_GrayValue/255.0f, _GrayValue/255.0f, _GrayValue/255.0f, _Alpha); }
void Window::fill(double _Red, double _Green, double _Blue)
    { glClearColor(_Red/255.0f, _Green/255.0f, _Blue/255.0f, 1); }
void Window::fill(double _Red, double _Green, double _Blue, double _Alpha)
    { glClearColor(_Red/255.0f, _Green/255.0f, _Blue/255.0f, _Alpha); }

void Window::fill(void) {
    Color clearColor = this->back;
    glClearColor(clearColor.r/255.0f, clearColor.g/255.0f, clearColor.b/255.0f, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}


void WindowUtils::FrameBufferSize_CallBack(GLFWwindow * _Window, int _Width, int _Height) {
    glViewport(0, 0, _Width, _Height);
}


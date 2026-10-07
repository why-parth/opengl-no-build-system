#ifndef GLH_Shader_Header
#define GLH_Shader_Header

#include "include/glh/buffer.hpp"
#include "include/glh/window.hpp"

class FileString {

    int __log__ = 1;

    public:
    char * file_name;
    char * source;
    static size_t BufferSize;
    int static_source = 0;

    FileString(void);
    FileString(const char * _FilePath);

    void free(void);

    ~FileString(void);

};

#define f_values << std::initializer_list<GLfloat>
#define i_values << std::initializer_list<GLint>
#define d_values << std::initializer_list<GLdouble>

class Shader : public FileString {

    
    public:
    int __log__ = 1;
    unsigned long int id;
    static char InfoLog[4096];
    static int RecentCompilationStatus;
    unsigned long int shader_type;
    char shader_type_string[32];

    Shader (void);

    Shader (const char * _FileName);

    void create (void);

    void operator << (const char * _Code);

    void operator % (const char * _ShaderType);

    void free (void);

};

class Program {

    public:
    int __log__ = 1; 
    unsigned long int id;
    int vertex_shader_linked = 0;
    int fragment_shader_linked = 0;
    static char InfoLog[4096];
    static int RecentLinkStatus;
    GLint RecentUniformLocation;

    AttributeData VAO;
    VertexData VBO;
    GLint _texture_assigned = 0;
    TextureData FontTexture; // Assignable

    Window * window;

    Program(void);

    Program& operator < (Shader &_Shader);
    Program& operator << (Shader &_Shader);
    Program& operator << (Window &_Window);

    void use(void);

    GLint locateUniform(const char *);

    void setUniform(GLfloat _F);
    void setUniform(GLfloat _F1, GLfloat _F2);
    void setUniform(GLfloat _F1, GLfloat _F2, GLfloat _F3);
    void setUniform(GLfloat _F1, GLfloat _F2, GLfloat _F3, GLfloat _F4);

    void setUniform(GLint _I);
    void setUniform(GLint _I1, GLint _I2);
    void setUniform(GLint _I1, GLint _I2, GLint _I3);
    void setUniform(GLint _I1, GLint _I2, GLint _I3, GLint _I4);

    void setUniform(GLdouble _D);
    void setUniform(GLdouble _D1, GLdouble _D2);
    void setUniform(GLdouble _D1, GLdouble _D2, GLdouble _D3);
    void setUniform(GLdouble _D1, GLdouble _D2, GLdouble _D3, GLdouble _D4);

    void setUniform(glm::mat4 _Mat4);
    void __setUniform(GLint _Location, glm::mat4 _Mat4);

    void operator==(GLint _Location);
    void operator==(const char * _Name);
    void operator<<(std::initializer_list<GLint> _Vector);
    void operator<<(std::initializer_list<GLfloat> _Vector);
    void operator<<(std::initializer_list<GLdouble> _Vector);

    void text(const char *, GLfloat _X, GLfloat _Y, float _Scale, glm::vec3 _Color);

    void font(TextureData & _Font);

};


#endif
#ifndef GLH_Buffer_Header
#define GLH_Buffer_Header

#include "include/glh/base.hpp"

typedef GLfloat VD_t;

// Revert the changes and make the VertexData and IndexData classes seperate, Aeay from the BindableBuffer Class.

class VertexData {

    public:

    static GLuint Usage;
    GLuint id;
    VD_t * buffer;
    std::vector<VD_t> static_buffer;
    GLuint type_byte_size = sizeof(VD_t);
    GLsizeiptr buffer_size;
    GLuint buffer_type = 0;
    GLuint stride = 0;

    void Constructor(void);

    VertexData(void);
    VertexData(VD_t _Buffer[], GLuint _Count);
    VertexData(std::vector<VD_t> _Buffer);
    VertexData(std::initializer_list<VD_t> _Buffer);

    void bind(void);
    void operator+ (void);

    void data(VD_t _Buffer[], GLuint _Count);
    void data(std::vector<VD_t> _Buffer);
    void data(std::initializer_list<VD_t> _Buffer);

    VertexData &operator << (std::vector<VD_t> _Buffer);

    VertexData &operator | (GLuint _Usage);
    VertexData &operator % (GLuint _Stride);

};

class IndexData {

    public:
    static GLuint Usage;
    GLuint id;
    GLuint * buffer;
    std::vector<GLuint> static_buffer;
    GLuint type_byte_size = sizeof(GLuint);
    GLsizeiptr buffer_size;
    GLuint buffer_type = 0;
    GLuint stride = 0;

    void Constructor(void);

    IndexData(void);
    IndexData(GLuint _Buffer[], GLuint _Count);
    IndexData(std::vector<GLuint> _Buffer);
    IndexData(std::initializer_list<GLuint> _Buffer);

    void bind(void);
    void operator+ (void);

    void data(GLuint _Buffer[], GLuint _Count);
    void data(std::vector<GLuint> _Buffer);
    void data(std::initializer_list<GLuint> _Buffer);

    IndexData &operator << (std::vector<GLuint> _Buffer);

    IndexData &operator | (GLuint _Usage);
    IndexData &operator % (GLuint _Stride);

};

class TextureData {

    public:
    int __log__ = 1;

    GLuint id;
    GLubyte * _buffer;
    GLint _wdith;
    GLint _height;
    GLint _n_channels;

    static GLuint GeneralActive;
    GLuint _active = 0;

    TextureData(void);
    TextureData(const char * _Path);

    void bind(void);
    void operator+ (void);

    void init(void);
    void make(void);

    static void ResetParameters(void);

    TextureData &load(const char * _Path);
    TextureData &operator << (const char * _Path);

    TextureData active (GLuint _Active);
    TextureData &operator >> (GLuint _Active);

};

class AttributeData {

    public:
    GLuint id;
    GLuint _location = 0;
    GLuint _count = 0;
    GLuint _vertex_data = 0;
    GLuint _index_data = 0;
    std::vector<GLuint> _vbo_id_stride_offset;

    GLuint index_stride = 1;
    GLuint start = 0;
    GLuint end = 3;

    GLuint DrawMode = GL_TRIANGLES;

    AttributeData (void);

    void bind(void);
    void operator+(void);


    AttributeData &stride(VertexData _VertexData, GLuint _Stride);
    AttributeData &operator()(VertexData _VertexData, GLuint _Stride);

    AttributeData &location(GLuint _Location);
    AttributeData &operator[](GLuint _Location);

    AttributeData &count(GLuint _Count);
    AttributeData &operator=(GLuint _Count);
    
    AttributeData &attribute(VertexData _VertexData);

    AttributeData &operator,(VertexData _VertexData);
    AttributeData &operator=(VertexData _VertexData);
    
    AttributeData &operator,(IndexData _IndexData);
    AttributeData &operator=(IndexData _IndexData);


    AttributeData &operator()(GLuint _Start, GLuint _End);
    void drawVertex(void);
    void drawIndex(void);

    void drawVertex(GLuint _Start, GLuint _Count);
    void drawIndex(GLuint _Start, GLuint _Count);

};


#endif
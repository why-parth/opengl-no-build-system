#define STB_IMAGE_IMPLEMENTATION
#include "include/glh/buffer.hpp"


GLuint VertexData::Usage = GL_STATIC_DRAW;

void VertexData::data (GLuint _ByteSize) {
    this->buffer_size = _ByteSize;
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, _ByteSize, NULL, VertexData::Usage);
}

void VertexData::data (std::initializer_list<VD_t> _Buffer) {
    this->static_buffer = _Buffer;
    this->buffer = this->static_buffer.data();
    this->buffer_size = _Buffer.size();
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, this->buffer_type_bytesize * _Buffer.size(), this->buffer, VertexData::Usage);
}

void VertexData::data (VD_t _Buffer[], GLuint _Count) {
    this->buffer = _Buffer;
    this->buffer_size = _Count;
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
    glBufferData(this->buffer_type, this->buffer_type_bytesize * _Count, _Buffer, VertexData::Usage);
}

void VertexData::data (std::vector<VD_t> _Buffer) {
    this->buffer = _Buffer.data();
    this->static_buffer = std::vector<VD_t>(_Buffer);
    this->buffer_size = _Buffer.size();
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, this->buffer_type_bytesize * _Buffer.size(), _Buffer.data(), VertexData::Usage);
}

void VertexData::bind(void) {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexData::operator+ (void) {
    this->bind();
}

VertexData &VertexData::operator<< (std::vector<VD_t> _Buffer) {
    this->data(_Buffer);
    return *this;
}

void VertexData::Constructor (void) {
    this->buffer_type = GL_ARRAY_BUFFER;
    glGenBuffers(1, &this->id);
}

VertexData::VertexData(void) {
    this->Constructor();
}

VertexData::VertexData(GLuint _ByteSize) {
    this->Constructor();
    this->data(_ByteSize);
}

VertexData::VertexData(VD_t _Buffer[], GLuint _Count) {
    this->Constructor();
    this->data(_Buffer, _Count);
}

VertexData::VertexData(std::vector<VD_t> _Buffer) {
    this->Constructor();
    this->data(_Buffer);
}

VertexData::VertexData(std::initializer_list<VD_t> _Buffer) {
    this->Constructor();
}

VertexData &VertexData::operator| (GLuint _Usage) {
    VertexData::Usage = _Usage;
    return *this;
}

VertexData &VertexData::operator% (GLuint _Stride) {
    this->stride = _Stride;
    return *this;
}



GLuint IndexData::Usage = GL_STATIC_DRAW;

void IndexData::data (GLuint _ByteSize) {
    this->buffer_size = _ByteSize;
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, _ByteSize, NULL, VertexData::Usage);
}

void IndexData::data (std::initializer_list<GLuint> _Buffer) {
    this->static_buffer = _Buffer;
    this->buffer = this->static_buffer.data();
    this->buffer_size = _Buffer.size();
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, this->buffer_type_bytesize * _Buffer.size(), this->buffer, IndexData::Usage);
}

void IndexData::data (GLuint _Buffer[], GLuint _Count) {
    this->buffer = _Buffer;
    this->buffer_size = _Count;
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, this->buffer_type_bytesize * _Count, _Buffer, IndexData::Usage);
}

void IndexData::data (std::vector<GLuint> _Buffer) {
    this->buffer = _Buffer.data();
    this->static_buffer = std::vector<GLuint>(_Buffer);
    this->buffer_size = _Buffer.size();
    glBindBuffer(this->buffer_type, this->id);
    glBufferData(this->buffer_type, this->buffer_type_bytesize * _Buffer.size(), _Buffer.data(), IndexData::Usage);
}

void IndexData::bind(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void IndexData::operator+ (void) {
    this->bind();
}

IndexData &IndexData::operator<< (std::vector<GLuint> _Buffer) {
    this->data(_Buffer);
    return *this;
}

void IndexData::Constructor (void) {
    this->buffer_type = GL_ELEMENT_ARRAY_BUFFER;
}

IndexData::IndexData(void) {
    this->Constructor();
    glGenBuffers(1, &this->id);
}

IndexData::IndexData(GLuint _ByteSize) {
    this->Constructor();
    this->data(_ByteSize);
}

IndexData::IndexData(GLuint _Buffer[], GLuint _Count) {
    this->Constructor();
}

IndexData::IndexData(std::vector<GLuint> _Buffer) {
    this->Constructor();
}

IndexData::IndexData(std::initializer_list<GLuint> _Buffer) {
    this->Constructor();
}

IndexData &IndexData::operator| (GLuint _Usage) {
    IndexData::Usage = _Usage;
    return *this;
}

IndexData &IndexData::operator% (GLuint _Stride) {
    this->stride = _Stride;
    return *this;
}



GLuint TextureData::GeneralActive = 0;

TextureData::TextureData(void) {
    TextureData::ResetParameters();
    this->_active = TextureData::GeneralActive++;
    glGenTextures(1, &this->id);
}

TextureData::TextureData(const char * _Path) {
    TextureData::ResetParameters();
    this->_active = TextureData::GeneralActive++;
    glGenTextures(1, &this->id);
    char * _Ext = (char *) std::strrchr(_Path, '.') + 1;
    if (!strcmp(_Ext, "ttf") || !strcmp(_Ext, "TTF")) this->font(_Path);
    else this->load(_Path);
}

void TextureData::bind(void) {
    glActiveTexture(GL_TEXTURE0 + this->_active);
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void TextureData::init(void) {
    glTexImage2D(GL_TEXTURE_2D, 0, this->_is_font ? GL_RED : GL_RGB, this->_wdith, this->_height, 0, this->_is_font ? GL_RED : GL_RGB, GL_UNSIGNED_BYTE, this->_buffer);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (!this->dont_free) {
        stbi_image_free(this->_buffer);
        this->dont_free = 1;
    }
}

void TextureData::make(void) {
    this->bind();
    this->init();
}

void TextureData::operator+ (void) {
    glActiveTexture(GL_TEXTURE0 + this->_active);
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void TextureData::ResetParameters(void) {
    stbi_set_flip_vertically_on_load(1); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);   

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   
}

TextureData &TextureData::load(const char * _Path) {
    this->_buffer = stbi_load(_Path, &this->_wdith, &this->_height, &this->_n_channels, 0);
    if (!this->_buffer) {
        ERR "Texture '" COLy << _Path << COLnone "' could not be loaded!";
        exit(-1);
    }
    this->_assigned = 1;
    return *this;
}

TextureData &TextureData::font(const char * _Path) {
    this->_is_font = 1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    FT_Library _FT;

    if (FT_Init_FreeType(&_FT)) {
        ERR COLr "Fatal" COLnone " error occured while initializing FreeType library!";
        exit(-1);
    }

    FT_Face _Face;
    if (FT_New_Face(_FT, _Path, 0, &_Face)) {
        ERR "Font '" COLy << _Path << COLnone "' could not be loaded!";
        exit(-1);
    }

    FT_Set_Pixel_Sizes(_Face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    this->dont_free = 1;

    glDeleteTextures(1, &this->id);

    for ( unsigned char c = 0; c < 128; c++)  {

        if (FT_Load_Char(_Face, c, FT_LOAD_RENDER)) {
            ERR "Glyph '" COLy << c << COLnone "' could not be loaded!";
            exit(-1);
        }   

        this->_wdith = _Face->glyph->bitmap.width;
        this->_height = _Face->glyph->bitmap.rows;
        this->_buffer = _Face->glyph->bitmap.buffer;

        glGenTextures(1, &this->id);
        this->bind();
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        this->init();

        _Char_t _Char = {
            this->id,
            glm::ivec2(this->_wdith, this->_height),
            glm::ivec2(_Face->glyph->bitmap_left, _Face->glyph->bitmap_top),
            _Face->glyph->advance.x
        };

        this->Chars.insert(std::pair<char, _Char_t>(c, _Char));

    }

    this->_buffer = NULL;
    FT_Done_Face(_Face);
    FT_Done_FreeType(_FT);
    LOGi "Font '" COLy << _Path << COLnone "' loaded." ALLnone;
    TextureData::ResetParameters();
    this->_assigned = 1;
    return *this;
}

TextureData &TextureData::operator << (const char * _Path) {
    char * _Ext = (char *) std::strrchr(_Path, '.') + 1;

    if (!strcmp(_Ext, "ttf") || !strcmp(_Ext, "TTF")) this->font(_Path);
    else this->load(_Path);
    
    return *this;
}

TextureData TextureData::active (GLuint _Active) {
    this->_active = _Active;
    if (this->_assigned) this->make();
    return *this;
}

TextureData &TextureData::operator >> (GLuint _Active) {
    this->_active = _Active;
    if (this->_assigned) this->make();
    return *this;
}



AttributeData::AttributeData(void) {
    glGenVertexArrays(1, &this->id);
}

void AttributeData::bind(void) {
    glBindVertexArray(this->id);
}

void AttributeData::operator+(void) {
    this->bind();
}

AttributeData &AttributeData::stride(VertexData _VertexData, GLuint _Stride) {
   int _assigned = 0;
    for (int i = 0; i < _vbo_id_stride_offset.size(); i += 3) {
        if (_VertexData.id == _vbo_id_stride_offset[i]) {
            _vbo_id_stride_offset[i+1] = _Stride;
            _assigned = 1;
            break;
        }
    }
    if (!_assigned) {
        this->_vbo_id_stride_offset.push_back(_VertexData.id);
        this->_vbo_id_stride_offset.push_back(_Stride);
        this->_vbo_id_stride_offset.push_back(0);
    }
    return *this;
}

AttributeData &AttributeData::operator()(VertexData _VertexData, GLuint _Stride) {
    this->stride(_VertexData, _Stride);
    return *this;
}


AttributeData &AttributeData::location(GLuint _Location) {
    this->_location = _Location;
    return *this;
}

AttributeData &AttributeData::operator[](GLuint _Location) {
    this->location(_Location);
    return *this;
}

AttributeData &AttributeData::count(GLuint _Count) {
    this->_count = _Count;
    return *this;
}

AttributeData &AttributeData::operator=(GLuint _Count) {
    this->count(_Count);
    return *this;
}

AttributeData &AttributeData::attribute(VertexData _VertexData) {
    GLuint _stride;
    GLuint _offset;
    int i = 0;
    for (; i < _vbo_id_stride_offset.size(); i += 3) {
        if (_VertexData.id == _vbo_id_stride_offset[i]) {
            if (!(_stride = _VertexData.stride)) _stride = _vbo_id_stride_offset[i+1];
            _offset = _vbo_id_stride_offset[i+2];
            break;
        }

    }
    glBindVertexArray(this->id);
    glBindBuffer(GL_ARRAY_BUFFER, _VertexData.id);
    glVertexAttribPointer(
        this->_location,
        this->_count,
        GL_FLOAT,
        GL_FALSE,
        _stride * sizeof(GLfloat),
        (void *)( _offset * sizeof(GLfloat) )
    );
    glEnableVertexAttribArray(this->_location);
    _vbo_id_stride_offset[i+2] += this->_count;
    return *this;
}

AttributeData &AttributeData::operator,(VertexData _VertexData) {
    this->attribute(_VertexData);
    return *this;
}

AttributeData &AttributeData::operator=(VertexData _VertexData) {
    this->attribute(_VertexData);
    return *this;
}

AttributeData &AttributeData::operator,(IndexData _IndexData) {
    this->index_stride = this->_count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IndexData.id);
    return *this;
}

AttributeData &AttributeData::operator=(IndexData _IndexData) {
    this->index_stride = this->_count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IndexData.id);
    return *this;
}


AttributeData &AttributeData::operator()(GLuint _Start, GLuint _End) {
    this->start = _Start;
    this->end = _End;
    return *this;
}


void AttributeData::drawVertex(void) {
    glBindVertexArray(this->id);
    glDrawArrays(this->DrawMode, this->start, this->end - this->start);
}

void AttributeData::drawIndex(void) {
    glBindVertexArray(this->id);
    glDrawElements(
        this->DrawMode,
        (this->end - this->start) * this->index_stride,
        GL_UNSIGNED_INT,
        (void *) (this->start * this->index_stride * sizeof(GLuint)));
}

void AttributeData::drawVertex(GLuint _Start, GLuint _Count) {
    glBindVertexArray(this->id);
    glDrawArrays(this->DrawMode, _Start, _Count);
    glBindVertexArray(0);
}

void AttributeData::drawIndex(GLuint _Start, GLuint _Count) {
    glBindVertexArray(this->id);
    glDrawElements(this->DrawMode, _Count * this->index_stride, GL_UNSIGNED_INT, (void *) (_Start * this->index_stride * sizeof(GLuint)));
    glBindVertexArray(0);
}

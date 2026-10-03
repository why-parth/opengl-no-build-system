#include "include/glh/shader.hpp"

size_t FileString::BufferSize = 4096;

FileString::FileString (void) {};
FileString::FileString (const char * _FilePath) {
    FILE * _FilePtr = fopen(_FilePath, "r");

    this->file_name = new char[sizeof(_FilePath) + 1];
    std::sprintf(this->file_name, "%s", _FilePath);
    
    if (!_FilePtr) {
        ERR "File '" COLy << _FilePath << COLnone "' could not be opened for reading!\n";
        exit(-1);
    }

    

    else {
        this->source = new char[BufferSize];
        long long int i = 0;
        for (char c = (long long int)fgetc(_FilePtr); !c || c != EOF; c = fgetc(_FilePtr), i++){
            if (i == BufferSize - 1) {
                source[i] = 0;
                WARN "File '" COLy << _FilePath << COLnone "' exceeds the buffer length.\n";
                break;
            }
            else source[i] = c;
        }
        source[i] = 0;
    }

    fclose(_FilePtr);
}

void FileString::free(void) {
    if (this->static_source) return;
    delete[] this->source;
    this->source = nullptr;
    delete[] this->file_name;
    this->file_name = nullptr;
}


FileString::~FileString(void) {
    if (this->source != nullptr) this->free();
}

char Shader::InfoLog[4096] = "\0";
int Shader::RecentCompilationStatus = 0;

Shader::Shader (void) {}
Shader::Shader (const char * _FileName) : FileString(_FileName) {}

void Shader::create (void) {
    this->id = glCreateShader(this->shader_type);

    glShaderSource(this->id, 1, &this->source, NULL);
    glCompileShader(this->id);
    
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &RecentCompilationStatus);
    if (!RecentCompilationStatus) {
        glGetShaderInfoLog(this->id, 1024, NULL, InfoLog);
        ERRb this->shader_type_string << " Shader" STYLEnone " could not be compiled\n";
        std::cout << InfoLog;
        exit(-1);
    }
}

void Shader::operator << (const char * _Code) {
    this->source = (char *)_Code;
    this->static_source = 1;
}

void Shader::operator % (const char * _ShaderType) {

    this->shader_type;
    std::sprintf(shader_type_string, "%s", _ShaderType);

    if (!strcmp(_ShaderType, "vertex")) this->shader_type = GL_VERTEX_SHADER;
    else if (!strcmp(_ShaderType, "fragment")) this->shader_type = GL_FRAGMENT_SHADER;
    else {
        ERR "No such shader type '" COLy << _ShaderType << COLnone "'exists!";
        exit(-1);
    }
    
    this->create();
}

void Shader::free(void) {
    FileString::free();
    glDeleteShader(this->id);
}

char Program::InfoLog[4096] = "\0";
int Program::RecentLinkStatus = 0;

Program::Program(void) {
    this->id = glCreateProgram();
}

Program& Program::operator < (Shader &_Shader) {
    glAttachShader(this->id, _Shader.id);

    if (_Shader.shader_type == GL_VERTEX_SHADER) this->vertex_shader_linked = 1;
    else if (_Shader.shader_type == GL_FRAGMENT_SHADER) this->fragment_shader_linked = 1;

    if (this->vertex_shader_linked && this->fragment_shader_linked) {
        glLinkProgram(this->id);

        glGetProgramiv(this->id, GL_LINK_STATUS, &Program::RecentLinkStatus);
        if (!Program::RecentLinkStatus) {
            glGetProgramInfoLog(this->id, 4096, NULL, Program::InfoLog);
            ERR "Shader Program could not be compiled!\n";
            std::cout << Program::InfoLog;
            exit(-1);
        }

        LOGi "Shader Program linked." COLnone;

        glUseProgram(this->id);
    }

    return *this;
}

Program& Program::operator << (Shader &_Shader) {
    Program & ret = this->operator<(_Shader);
    _Shader.free();
    return ret;
}

void Program::use(void) {
    glUseProgram(this->id);
}

GLint Program::locateUniform(const char * _Name) {
    return this->RecentUniformLocation = glGetUniformLocation(this->id, _Name);
}

void Program::setUniform(GLfloat _F) {
    glUseProgram(this->id);
    glUniform1f(this->RecentUniformLocation, _F);
}

void Program::setUniform(GLfloat _F1, GLfloat _F2) {
    glUseProgram(this->id);
    glUniform2f(this->RecentUniformLocation, _F1, _F2);
}

void Program::setUniform(GLfloat _F1, GLfloat _F2, GLfloat _F3) {
    glUseProgram(this->id);
    glUniform3f(this->RecentUniformLocation, _F1, _F2, _F3);
}

void Program::setUniform(GLfloat _F1, GLfloat _F2, GLfloat _F3, GLfloat _F4) {
    glUseProgram(this->id);
    glUniform4f(this->RecentUniformLocation, _F1, _F2, _F3, _F4);
}

void Program::setUniform(GLint _I) {
    glUseProgram(this->id);
    glUniform1i(this->RecentUniformLocation, _I);
}

void Program::setUniform(GLint _I1, GLint _I2) {
    glUseProgram(this->id);
    glUniform2i(this->RecentUniformLocation, _I1, _I2);
}

void Program::setUniform(GLint _I1, GLint _I2, GLint _I3) {
    glUseProgram(this->id);
    glUniform3i(this->RecentUniformLocation, _I1, _I2, _I3);
}

void Program::setUniform(GLint _I1, GLint _I2, GLint _I3, GLint _I4) {
    glUseProgram(this->id);
    glUniform4i(this->RecentUniformLocation, _I1, _I2, _I3, _I4);
}

void Program::setUniform(GLdouble _D) {
    glUseProgram(this->id);
    glUniform1d(this->RecentUniformLocation, _D);
}

void Program::setUniform(GLdouble _D1, GLdouble _D2) {
    glUseProgram(this->id);
    glUniform2d(this->RecentUniformLocation, _D1, _D2);
}

void Program::setUniform(GLdouble _D1, GLdouble _D2, GLdouble _D3) {
    glUseProgram(this->id);
    glUniform3d(this->RecentUniformLocation, _D1, _D2, _D3);
}

void Program::setUniform(GLdouble _D1, GLdouble _D2, GLdouble _D3, GLdouble _D4) {
    glUseProgram(this->id);
    glUniform4d(this->RecentUniformLocation, _D1, _D2, _D3, _D4);
}

void Program::setUniform(glm::mat4 _Mat4) {
    glUseProgram(this->id);
    glUniformMatrix4fv(this->RecentUniformLocation, 1, GL_FALSE, glm::value_ptr(_Mat4));
}

void Program::__setUniform(GLint _Location, glm::mat4 _Mat4) {
    glUseProgram(this->id);
    glUniformMatrix4fv(_Location, 1, GL_FALSE, glm::value_ptr(_Mat4));
}


void Program::operator==(GLint _Location) {
    this->RecentUniformLocation = _Location;
}

void Program::operator==(const char * _Name) {
    this->RecentUniformLocation = glGetUniformLocation(this->id, _Name);
}

void Program::operator<<(std::initializer_list<GLint> _Vector){
    GLint * data = (GLint *)_Vector.begin();
    switch (_Vector.size())
    {
    case 0:
        ERR "Pass at least 1 value via the uniform!";
        exit(-1);
    case 1: this->setUniform(data[0]); break;
    case 2: this->setUniform(data[0], data[1]); break;
    case 3: this->setUniform(data[0], data[1], data[2]); break;
    case 4: this->setUniform(data[0], data[1], data[2], data[3]); break;
    default:
        ERR "More than 4 values can not be passed via one uniform!";
        exit(-1);
    }
}

void Program::operator<<(std::initializer_list<GLfloat> _Vector){
    GLfloat * data = (GLfloat *)_Vector.begin();
    switch (_Vector.size())
    {
    case 0:
        ERR "Pass at least 1 value via the uniform!";
        exit(-1);
    case 1: this->setUniform(data[0]); break;
    case 2: this->setUniform(data[0], data[1]); break;
    case 3: this->setUniform(data[0], data[1], data[2]); break;
    case 4: this->setUniform(data[0], data[1], data[2], data[3]); break;
    default:
        ERR "More than 4 values can not be passed via one uniform!";
        exit(-1);
    }
}

void Program::operator<<(std::initializer_list<GLdouble> _Vector){
    GLdouble * data = (GLdouble *)_Vector.begin();
    switch (_Vector.size())
    {
    case 0:
        ERR "Pass at least 1 value via the uniform!";
        exit(-1);
    case 1: this->setUniform(data[0]); break;
    case 2: this->setUniform(data[0], data[1]); break;
    case 3: this->setUniform(data[0], data[1], data[2]); break;
    case 4: this->setUniform(data[0], data[1], data[2], data[3]); break;
    default:
        ERR "More than 4 values can not be passed via one uniform!";
        exit(-1);
    }
}



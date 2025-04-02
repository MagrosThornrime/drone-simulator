#include <Shader.h>
#include <Logger.h>


GLint chooseShader(ShaderType type){
    GLint shader = 0;
    switch(type){
        case vertex:
            shader = GL_VERTEX_SHADER;
            break;
        case fragment:
            shader = GL_FRAGMENT_SHADER;
            break;
        case geometry:
            shader = GL_GEOMETRY_SHADER;
            break;
    }
    return shader;
}

std::string shaderToString(ShaderType type){
    std::string shader;
    switch(type){
        case vertex:
            shader = "vertex";
            break;
        case fragment:
            shader = "fragment";
            break;
        case geometry:
            shader = "geometry";
            break;
    }
    return shader;
}


void Shader::_compileShader(unsigned int &shader, ShaderType type, const std::string& code) {
    const char* charCode = code.c_str();
    shader = glCreateShader(chooseShader(type));
    glShaderSource(shader, 1, &charCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &_success);
    if(_success != GL_TRUE) {
        glGetShaderInfoLog(shader, 512, NULL, _infoLog);
        std::string message = shaderToString(type) + " shader compilation failed: " + std::string(_infoLog);
        Logger::log(message, LogLevel::error);
    }
}

void Shader::_linkProgram() {
    glAttachShader(ID, _vertex);
    glAttachShader(ID, _fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &_success);
    if(_success != GL_TRUE){
        glGetProgramInfoLog(ID, 512, NULL, _infoLog);
        std::string message = "shader program linking failed: " + std::string(_infoLog);
        Logger::log(message, LogLevel::error);
    }
}

void Shader::_addShaders(bool geometry){
    _compileShader(_vertex, ShaderType::vertex, _vertexCode);
    _compileShader(_fragment, ShaderType::fragment, _fragmentCode);
    if(geometry)
        _compileShader(_geometry, ShaderType::geometry, _geometryCode);
    _linkProgram();
    glDeleteShader(_vertex);
    glDeleteShader(_fragment);
    if(geometry)
        glDeleteShader(_geometry);
}

void Shader::compileProgram() {
    ID = glCreateProgram();
    if(_geometryCode.empty())
        _addShaders(false);
    else
        _addShaders(true);
}

Shader::~Shader(){
    glDeleteProgram(ID);
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector2f(const std::string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVector2f(const std::string& name, const glm::vec2& value) const {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y);
}

void Shader::setVector3f(const std::string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVector3f(const std::string& name, const glm::vec3& value) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVector4f(const std::string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setVector4f(const std::string& name, const glm::vec4& value) const {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const std::string& name, glm::mat4 value) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
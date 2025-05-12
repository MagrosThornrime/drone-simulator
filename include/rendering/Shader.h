#pragma once
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <string>
#include <utility>


enum ShaderType {vertex, fragment, geometry};

GLint chooseShader(ShaderType type);

std::string shaderToString(ShaderType type);

class Shader{
    unsigned int _vertex{}, _fragment{}, _geometry{};
    std::string _vertexCode, _fragmentCode, _geometryCode;
    int _success{};
    char _infoLog[512]{};

    void _compileShader(unsigned int& shader, ShaderType type, const std::string& code);
    void _linkProgram();
    void _addShaders(bool geometry = false);

public:
    unsigned int ID{};

    void compileProgram();

    Shader(std::string  vertexCode, std::string  fragmentCode)
    : _vertexCode(std::move(vertexCode)), _fragmentCode(std::move(fragmentCode)) {}

    Shader(std::string  vertexCode, std::string  fragmentCode,
                  std::string  geometryCode)
    : _vertexCode(std::move(vertexCode)), _fragmentCode(std::move(fragmentCode)),
    _geometryCode(std::move(geometryCode)) {}

    Shader() = default;

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    void setVector2f (const std::string& name, float x, float y) const;
    void setVector2f (const std::string& name, const glm::vec2 &value) const;
    void setVector3f (const std::string& name, float x, float y, float z) const;
    void setVector3f (const std::string& name, const glm::vec3 &value) const;
    void setVector4f (const std::string& name, float x, float y, float z, float w) const;
    void setVector4f (const std::string& name, const glm::vec4 &value) const;

    void setMatrix4(const std::string& name, glm::mat4 value) const;
};
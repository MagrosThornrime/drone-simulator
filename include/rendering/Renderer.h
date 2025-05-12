#pragma once
#include <rendering/Shader.h>
#include <rendering/Model.h>

class Renderer
{
    float _windowWidth, _windowHeight;

    glm::vec3 _lightColor = glm::vec3(1.0f);
    glm::vec4 _backgroundColor = glm::vec4(0.449f, 0.686f, 0.784f, 1.0f);
    glm::vec3 _lightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
    Shader* _shader{};
    glm::mat4 _viewMatrix;

    glm::mat4 _getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
    glm::mat4 _getProjectionMatrix();

public:
    float zoom{};

    Renderer(Shader* shader, float windowWidth, float windowHeight);
    Renderer(const Renderer&) = delete;
    ~Renderer();
    void drawBackground();
    void drawModel(Model* model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
    void setViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up);

};

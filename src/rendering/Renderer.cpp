#include <rendering/Renderer.h>
#include <glad/glad.h>
#include <Logger.h>

#include <Application.h>

void Renderer::drawBackground(){
    glClearColor(0.449f, 0.686f, 0.784f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawModel(Model* model, glm::vec3 position, glm::vec3 scale,
    glm::vec3 rotationAxis, float rotationAngle)
{
    _shader->use();
    _shader->setVector3f("lightDirection", _lightDirection);
    _shader->setVector3f("lightColor", _lightColor);
    glm::mat4 modelMatrix = _getModelMatrix(position, scale, rotationAxis, rotationAngle);
    glm::mat4 projectionMatrix = _getProjectionMatrix();
    _shader->setMatrix4("model", modelMatrix);
    _shader->setMatrix4("view", _viewMatrix);
    _shader->setMatrix4("projection", projectionMatrix);
    model->draw(*_shader);
}

glm::mat4 Renderer::_getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    model = glm::translate(model, position);
    return model;
}

glm::mat4 Renderer::_getProjectionMatrix()
{
    float width = Application::windowWidth;
    float height = Application::windowHeight;
    return glm::perspective(glm::radians(zoom), width / height, 0.1f, 100.0f);
}

void Renderer::setViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    _viewMatrix = glm::lookAt(position, position + front, up);
}


void Renderer::initialize(Shader* shader)
{
    _lightColor = glm::vec3(1.0f);
    _lightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);
    _shader = shader;
    Logger::log("Renderer started", info);
}

void Renderer::destroy()
{
    Logger::log("Renderer stopped", info);
}
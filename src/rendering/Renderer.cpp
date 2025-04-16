#include <rendering/Renderer.h>
#include <glad/glad.h>
#include <Logger.h>

#include <Application.h>

void Renderer::drawBackground(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawModel(Model* model, glm::vec3 position, glm::vec3 scale,
    glm::vec3 rotationAxis, float rotationAngle)
{
    _shader->use();
    glm::mat4 modelMatrix = _getModelMatrix(position, scale, rotationAxis, rotationAngle);
    glm::mat4 viewMatrix = _getViewMatrix();
    glm::mat4 projectionMatrix = _getProjectionMatrix();
    _shader->setMatrix4("model", modelMatrix);
    _shader->setMatrix4("view", viewMatrix);
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
    float width = Application::getWindowWidth();
    float height = Application::getWindowHeight();
    return glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
}

glm::mat4 Renderer::_getViewMatrix()
{
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::rotate(view, glm::radians(15.f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, -1.0f, -3.0f));
    return view;
}


void Renderer::initialize(Shader* shader)
{
    _shader = shader;
    Logger::log("Renderer started", info);
}

void Renderer::destroy()
{
    Logger::log("Renderer stopped", info);
}
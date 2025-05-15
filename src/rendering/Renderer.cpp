#include <rendering/Renderer.h>
#include <glad/glad.h>
#include <Logger.h>
#include <Application.h>


void Renderer::drawBackground(){
    glClearColor(_backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::drawModel(Model* model, glm::vec3 position, glm::vec3 scale)
{
    _shader->use();
    _shader->setVector3f("lightDirection", _lightDirection);
    _shader->setVector3f("lightColor", _lightColor);
    glm::mat4 modelMatrix = _getModelMatrix(position, scale);
    glm::mat4 projectionMatrix = _getProjectionMatrix();
    _shader->setMatrix4("model", modelMatrix);
    _shader->setMatrix4("view", _viewMatrix);
    _shader->setMatrix4("projection", projectionMatrix);
    model->draw(*_shader);
}

glm::mat4 Renderer::_getModelMatrix(glm::vec3 position, glm::vec3 scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale);
    model = glm::translate(model, position);
    return model;
}

glm::mat4 Renderer::_getProjectionMatrix()
{
    return glm::perspective(glm::radians(zoom), _windowWidth / _windowHeight,
        _renderRangeMin, _renderRangeMax);
}

void Renderer::setViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up)
{
    _viewMatrix = glm::lookAt(position, position + front, up);
}


Renderer::Renderer(Shader* shader, float windowWidth, float windowHeight, float renderRangeMin, float renderRangeMax)
    : _windowWidth(windowWidth), _windowHeight(windowHeight), _renderRangeMin(renderRangeMin),
    _renderRangeMax(renderRangeMax)
{
    _shader = shader;
    Logger::log("Renderer started", info);
}

Renderer::~Renderer()
{
    Logger::log("Renderer stopped", info);
}
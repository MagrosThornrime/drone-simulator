#include <rendering/Renderer.h>
#include <glad/glad.h>
#include <Logger.h>

#include <Application.h>

#include "rendering/Model.h"

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

void Renderer::_initData()
{
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    //      0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //      0.0f,  0.5f, 0.0f, 0.5f, 1.0f
    // };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Renderer::initialize(Shader* shader)
{
    _shader = shader;
    _initData();
    Logger::log("Renderer started", info);
}

void Renderer::destroy()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    Logger::log("Renderer stopped", info);
}
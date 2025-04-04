#include <rendering/Renderer.h>
#include <glad/glad.h>

#include <Logger.h>

void Renderer::drawBackground(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawSprite()
{
    _shader->use();
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::_initData()
{
    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };


    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
}

Renderer::Renderer(Shader* shader) : _shader(shader)
{
    _initData();
    Logger::log("Renderer started", info);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    Logger::log("Renderer stopped", info);
}
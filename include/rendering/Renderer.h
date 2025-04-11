#pragma once
#include "Shader.h"
#include <rendering/Texture.h>

#include "Model.h"

class Renderer
{
    Shader* _shader;
    unsigned int _vao{}, _vbo{};
    int triangles = 36;

    void _initData();
    glm::mat4 _getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
    glm::mat4 _getProjectionMatrix();
    glm::mat4 _getViewMatrix();

public:
    Renderer(Shader* shader);
    ~Renderer();
    void drawBackground();
    void drawModel(Model* model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
};

#pragma once
#include "Shader.h"
#include <rendering/Texture.h>

#include "Model.h"

class Renderer
{
    static inline Shader* _shader{};
    static inline unsigned int _vao{}, _vbo{};
    static inline int triangles = 36;

    static void _initData();
    static glm::mat4 _getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
    static glm::mat4 _getProjectionMatrix();
    static glm::mat4 _getViewMatrix();

public:
    static void initialize(Shader* shader);
    static void destroy();
    static void drawBackground();
    static void drawModel(Model* model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
};

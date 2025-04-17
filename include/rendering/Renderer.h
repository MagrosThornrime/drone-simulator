#pragma once
#include <rendering/Shader.h>
#include <rendering/Model.h>

class Renderer
{
    static inline Shader* _shader{};
    static inline glm::mat4 _viewMatrix{};

    static glm::mat4 _getModelMatrix(glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
    static glm::mat4 _getProjectionMatrix();

public:
    static inline float zoom{};

    static void initialize(Shader* shader);
    static void destroy();
    static void drawBackground();
    static void drawModel(Model* model, glm::vec3 position, glm::vec3 scale, glm::vec3 rotationAxis, float rotationAngle);
    static void setViewMatrix(glm::vec3 position, glm::vec3 front, glm::vec3 up);

};

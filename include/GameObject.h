#pragma once
#include <glm/vec3.hpp>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>


class GameObject
{
    std::string _modelName;

protected:
    glm::vec3 _position;
    glm::vec3 _rotationAxis;
    glm::vec3 _scale;
    float _rotationAngle;

public:
    GameObject() = default;
    GameObject(const std::string& modelName, glm::vec3 position, glm::vec3 scale,
        glm::vec3 rotationAxis, float rotationAngle) : _modelName(modelName), _position(position),
        _rotationAxis(rotationAxis), _scale(scale), _rotationAngle(rotationAngle) {}

    void draw(Renderer& renderer, AssetManager& assetManager)
    {
        Model* model = assetManager.getModel(_modelName);
        renderer.drawModel(model, _position, _scale, _rotationAxis, _rotationAngle);
    }
};

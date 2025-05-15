#pragma once
#include <glm/vec3.hpp>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>


class GameObject
{
protected:
    std::string _modelName;
    glm::vec3 _position;
    glm::vec3 _scale;
    float _yaw = -90.0f;
    float _pitch = 0.0f;

public:
    virtual ~GameObject() = default;
    GameObject() = default;
    GameObject(const GameObject& other) = default;
    GameObject(const std::string& modelName, glm::vec3 position, glm::vec3 scale)
    : _modelName(modelName), _position(position),_scale(scale) {}

    virtual void draw(Renderer& renderer, AssetManager& assetManager)
    {
        Model* model = assetManager.getModel(_modelName);
        renderer.drawModel(model, _position, _scale);
    }
};

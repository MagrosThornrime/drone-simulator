#pragma once
#include <glm/vec3.hpp>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>
#include <collisions/Collider.h>


class GameObject
{
protected:
    std::string _modelName;
    glm::vec3 _position;
    glm::vec3 _scale;
    float _yaw = -90.0f;
    float _pitch = 0.0f;
    Collider _collider;

    virtual void _fillCollider(AssetManager& assetManager);
    void _calculateModelMatrix();

public:
    glm::mat4 modelMatrix;

    virtual ~GameObject() = default;
    GameObject() = default;
    GameObject(const GameObject& other) = default;
    GameObject(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager);

    virtual void draw(Renderer& renderer, AssetManager& assetManager);
    bool collidesWith(const GameObject& other) const;
};

#pragma once
#include <game_objects/GameObject.h>

#include "Terrain.h"

enum MovementDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


class Player : public GameObject
{
    glm::vec3 _front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _right;
    glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    // camera options
    float _movementSpeed = 50.0f;
    float _mouseSensitivity = 0.1f;
    float _zoom = 90.0f;
    float _cameraDistance;

    glm::vec3 _getCameraPosition();

public:
    Player(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager,
        float cameraDistance);

    Player();

    void updateViewZone(Renderer& renderer);

    void move(MovementDirection direction, float deltaTime, const std::vector<GameObject*>& collidables);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    float getZoom() const;
    void _updateVectors();
};

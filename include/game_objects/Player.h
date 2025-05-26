#pragma once
#include <game_objects/GameObject.h>

enum MovementDirection {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum CameraMode
{
    FIRST_PERSON,
    THIRD_PERSON,
    TOP_DOWN
};


class Player : public GameObject
{
    glm::vec3 _front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _right;
    glm::vec3 _worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 _moveFront = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 _moveRight;
    // camera options
    float _movementSpeed;

    float _mouseSensitivity;
    float _zoom;
    CameraMode _cameraMode = THIRD_PERSON;

    glm::vec3 _getCameraPosition();
    void _updateVectors();


public:
    Player(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager);

    Player();

    void updateViewZone(Renderer& renderer);

    void move(MovementDirection direction, float deltaTime, const std::vector<GameObject*>& collidables);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void setCameraMode(CameraMode mode);
    float getZoom() const;
    void draw(Renderer& renderer, AssetManager& assetManager) override;
};

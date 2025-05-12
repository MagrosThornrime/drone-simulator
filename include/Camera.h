#pragma once
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    // camera Attributes
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right;
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    // euler Angles
    float yaw = -90.0f;
    float pitch = 0.0f;
    // camera options
    float movementSpeed = 2.5f;
    float mouseSensitivity = 0.1f;
    float zoom = 45.0f;

    Camera();

    Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float movementSpeed,
        float mouseSensitivity);


    void move(CameraMovement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void _updateCameraVectors();
};
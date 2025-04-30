#include <Camera.h>

Camera::Camera()
{
    _updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, float yaw, float pitch, float movementSpeed,
        float mouseSensitivity) : position(position), front(front), worldUp(up), yaw(yaw),
        pitch(pitch), movementSpeed(movementSpeed), mouseSensitivity(mouseSensitivity)
{
    _updateCameraVectors();
}

void Camera::move(CameraMovement direction, float deltaTime)
{
    float velocity = movementSpeed * deltaTime;

    switch (direction)
    {
    case FORWARD:
        position += front * velocity;
        return;
    case BACKWARD:
        position -= front * velocity;
        return;
    case LEFT:
        position -= right * velocity;
        return;
    case RIGHT:
        position += right * velocity;
    }
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    _updateCameraVectors();
}


void Camera::_updateCameraVectors()
{
    // calculate the new Front vector
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
#include <game_objects/Player.h>

#include "game_objects/Terrain.h"

Player::Player(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager)
    : GameObject(modelName, position, scale, assetManager)
{
    _updateVectors();
}

Player::Player() : GameObject()
{
    _updateVectors();
}

glm::vec3 Player::_getCameraPosition()
{
    return _position - _front * 200.0f;
}

void Player::updateViewZone(Renderer& renderer)
{
    renderer.setViewMatrix(_getCameraPosition(), _front, _up);
}

void Player::move(MovementDirection direction, float deltaTime)
{
    float velocity = _movementSpeed * deltaTime;

    switch (direction)
    {
    case FORWARD:
        _position += _front * velocity;
        return;
    case BACKWARD:
        _position -= _front * velocity;
        return;
    case LEFT:
        _position -= _right * velocity;
        return;
    case RIGHT:
        _position += _right * velocity;
        return;
    case UP:
        _position += _up * velocity;
        return;
    case DOWN:
        _position -= _up * velocity;
    }
}

void Player::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (_pitch > 89.0f)
            _pitch = 89.0f;
        if (_pitch < -89.0f)
            _pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    _updateVectors();
}

float Player::getZoom() const
{
    return _zoom;
}

void Player::_updateVectors()
{
    // calculate the new Front vector
    _front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front.y = sin(glm::radians(_pitch));
    _front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(_front);
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}
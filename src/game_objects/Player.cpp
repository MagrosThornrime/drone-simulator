#include <game_objects/Player.h>
#include <game_objects/Terrain.h>

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
    return _position - _front * 500.0f;
}

void Player::updateViewZone(Renderer& renderer)
{
    renderer.setViewMatrix(_getCameraPosition(), _front, _up);
}

void Player::move(MovementDirection direction, float deltaTime, const std::vector<GameObject*>& collidables)
{
    float velocity = _movementSpeed * deltaTime;

    glm::vec3 lastPosition = _position;

    switch (direction)
    {
    case FORWARD:
        _position += _front * velocity;
        break;
    case BACKWARD:
        _position -= _front * velocity;
        break;
    case LEFT:
        _position -= _right * velocity;
        break;
    case RIGHT:
        _position += _right * velocity;
        break;
    case UP:
        _position += _worldUp * velocity;
        break;
    case DOWN:
        _position -= _worldUp * velocity;
    }
    _collider.setDynamicVertices(_position, _scale);
    for (auto& collidable : collidables)
    {
        if (collidesWith(*collidable))
        {
            _position = lastPosition;
            _collider.setDynamicVertices(_position, _scale);
            return;
        }
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
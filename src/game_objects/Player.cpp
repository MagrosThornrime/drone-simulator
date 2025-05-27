#include <game_objects/Player.h>

Player::Player(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager)
    : GameObject(modelName, position, scale, assetManager)
{
    _movementSpeed = assetManager.playerVelocity;
    _mouseSensitivity = assetManager.playerMouseSensitivity;
    _zoom = assetManager.playerZoom;
    _updateVectors();
}

Player::Player() : GameObject()
{
    _updateVectors();
}

glm::vec3 Player::_getCameraPosition()
{
    glm::vec3 cameraOffset;
    switch (_cameraMode)
    {
        case THIRD_PERSON:
            cameraOffset = _front * 10.0f;
            break;
        case FIRST_PERSON:
            cameraOffset = glm::vec3(0.0f);
            break;
        case TOP_DOWN:
            cameraOffset = -_worldUp * 10.0f;
    }
    return _position - cameraOffset;
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
        _position += _moveFront * velocity;
        break;
    case BACKWARD:
        _position -= _moveFront * velocity;
        break;
    case LEFT:
        _position -= _moveRight * velocity;
        break;
    case RIGHT:
        _position += _moveRight * velocity;
        break;
    case UP:
        _position += _worldUp * velocity;
        break;
    case DOWN:
        _position -= _worldUp * velocity;
    }
    _calculateModelMatrix();
    _collider.setDynamicVertices(modelMatrix, _scale);
    for (auto& collidable : collidables)
    {
        if (collidesWith(*collidable))
        {
            _position = lastPosition;
            _calculateModelMatrix();
            _collider.setDynamicVertices(modelMatrix, _scale);
            return;
        }
    }
}

void Player::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    if (_cameraMode == TOP_DOWN)
    {
        return;
    }
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
    if (_cameraMode == TOP_DOWN)
    {
        _front = glm::vec3(0.0f, -1.0f, 0.0f);
        _up = glm::normalize(glm::vec3(_moveFront.x, 0.0f, _moveFront.z));
        _right = glm::normalize(glm::vec3(_moveFront.z, 0.0f, -_moveFront.x));
        _moveFront = glm::normalize(glm::vec3(_moveFront.x, 0.0f, _moveFront.z));
        _moveRight = glm::normalize(glm::vec3(_moveRight.x, 0.0f, _moveRight.z));
        return;
    }
    // calculate the new Front vector
    _front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front.y = sin(glm::radians(_pitch));
    _front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(_front);
    _moveFront = _front;
    // also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _moveRight = _right;
    _up = glm::normalize(glm::cross(_right, _front));
}

void Player::setCameraMode(CameraMode mode)
{
    _cameraMode = mode;
    _updateVectors();
}

void Player::draw(Renderer& renderer, AssetManager& assetManager)
{
    if (_cameraMode == FIRST_PERSON)
    {
        return;
    }
    GameObject::draw(renderer, assetManager);
}

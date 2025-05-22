#include <terrain/Chunk.h>

void Chunk::_appendFace(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight,
    glm::vec3 normalTop, glm::vec3 normalBottom, std::vector<VertexData>& vertices,
    std::vector<unsigned int>& indices)
{
    int startingVertices = vertices.size();

    vertices.emplace_back(bottomLeft, normalTop, _texBackwardLeft);
    vertices.emplace_back(topLeft, normalTop, _texForwardLeft);
    vertices.emplace_back(topRight, normalTop, _texForwardRight);
    vertices.emplace_back(bottomRight, normalBottom, _texBackwardRight);

    for (int i : {0, 1, 2})
    {
        indices.push_back(startingVertices + i);
    }
    for (int i : {2, 3, 0})
    {
        indices.push_back(startingVertices + i);
    }
}

void Chunk::_generateNormalsUp()
{
    glm::vec3 leftEdge = _upForwardLeft - _upBackwardLeft;
    glm::vec3 diagonal = _upForwardRight - _upBackwardLeft;
    glm::vec3 forward = glm::cross(leftEdge, diagonal);
    if (forward.y < 0.0f)
    {
        forward *= -1.0f;
    }
    _normalUpForward = normalize(forward);

    glm::vec3 bottomEdge = _upBackwardRight - _upBackwardLeft;
    glm::vec3 backward = glm::cross(bottomEdge, diagonal);
    if (backward.y < 0.0f)
    {
        backward *= -1.0f;
    }
    _normalUpBackward = normalize(backward);
}

Chunk::Chunk(glm::vec3 upBackwardLeft, glm::vec3 upBackwardRight, glm::vec3 upForwardLeft, glm::vec3 upForwardRight,
    float minY, float maxY) : _upBackwardLeft(upBackwardLeft), _upBackwardRight(upBackwardRight),
    _upForwardLeft(upForwardLeft), _upForwardRight(upForwardRight)
{
    _downBackwardLeft = {_upBackwardLeft.x, minY, _upBackwardLeft.z};
    _downForwardLeft = {_upForwardLeft.x, minY, _upForwardLeft.z};
    _downBackwardRight = {_upBackwardRight.x, minY, _upBackwardRight.z};
    _downForwardRight = {_upForwardRight.x, minY, _upForwardRight.z};
    _generateNormalsUp();
}

void Chunk::append(std::vector<VertexData>& vertices, std::vector<unsigned int>& indices)
{
    // up face
    _appendFace(_upBackwardLeft, _upBackwardRight, _upForwardLeft, _upForwardRight,
        _normalUpForward, _normalUpBackward,
        vertices, indices);

    // left face
    _appendFace(_downBackwardLeft, _downForwardLeft, _upBackwardLeft, _upForwardRight,
        _normalLeft, _normalLeft,
        vertices, indices);

    // right face
    _appendFace(_downForwardRight, _downBackwardRight, _upForwardRight, _upBackwardRight,
        _normalRight, _normalRight,
        vertices, indices);

    // forward face
    _appendFace(_downForwardLeft, _downForwardRight, _upForwardLeft, _upForwardRight,
    _normalForward, _normalForward,
            vertices, indices);

    // backward face
    _appendFace(_downBackwardRight, _downBackwardLeft, _upBackwardRight, _upBackwardLeft,
        _normalBackward, _normalBackward,
        vertices, indices);

    // down face
    _appendFace(_downBackwardLeft, _downBackwardRight, _upBackwardLeft, _upBackwardRight,
        _normalDown, _normalDown,
        vertices, indices);
}

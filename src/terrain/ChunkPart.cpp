#include <terrain/ChunkPart.h>

void ChunkPart::_calculateBottomVertices()
{
    std::vector allY = {_upVertex1.y, _upVertex2.y, _upVertex3.y};
    float minY = *std::min_element(allY.begin(), allY.end());

    _downVertex1 = {_upVertex1.x, minY - _height, _upVertex1.z};
    _downVertex2 = {_upVertex2.x, minY - _height, _upVertex2.z};
    _downVertex3 = {_upVertex3.x, minY - _height, _upVertex3.z};
}

void ChunkPart::_calculateNormalUp()
{
    glm::vec3 up13 = _upVertex3 - _upVertex1;
    glm::vec3 up12 = _upVertex2 - _upVertex1;

    _normalUp = normalize(cross(up13, up12));
    if (_normalUp.y < 0.0f)
    {
        _normalUp *= -1.0f;
    }
}

void ChunkPart::_appendVertices(std::vector<VertexData>& vertices)
{
    if (_isUpperLeftCorner)
    {
        vertices.emplace_back(_upVertex1, _normalUp, _texBottomLeft);
        vertices.emplace_back(_upVertex2, _normalUp, _texTopLeft);
        vertices.emplace_back(_upVertex3, _normalUp, _texTopRight);
        vertices.emplace_back(_downVertex1, _normalUp, _texBottomLeft);
        vertices.emplace_back(_downVertex2, _normalUp, _texTopLeft);
        vertices.emplace_back(_downVertex3, _normalUp, _texTopRight);
    }
    else
    {
        vertices.emplace_back(_upVertex1, _normalUp, _texTopRight);
        vertices.emplace_back(_upVertex2, _normalUp, _texBottomRight);
        vertices.emplace_back(_upVertex3, _normalUp, _texBottomLeft);
        vertices.emplace_back(_downVertex1, _normalUp, _texTopRight);
        vertices.emplace_back(_downVertex2, _normalUp, _texBottomRight);
        vertices.emplace_back(_downVertex3, _normalUp, _texBottomLeft);
    };
}

void ChunkPart::_appendFaces(int startSize, std::vector<unsigned int>& indices)
{
    std::vector<std::vector<unsigned int>> faces = {
        // top face
        {0, 1, 2},
        // down face
        {3, 4, 5},
        // side 1
        {0, 1, 4},
        {4, 3, 0},
        // side 2
        {1, 2, 5},
        {5, 4, 1},
        // side 3
        {0, 2, 5},
        {5, 3, 0}
    };

    for (auto& face : faces)
    {
        for (auto index : face)
        {
            indices.push_back(index + startSize);
        }
    }
}

ChunkPart::ChunkPart(glm::vec3 upVertex1, glm::vec3 upVertex2, glm::vec3 upVertex3, float height, bool isUpperLeftCorner)
    : _upVertex1(upVertex1), _upVertex2(upVertex2), _upVertex3(upVertex3), _height(height),
    _isUpperLeftCorner(isUpperLeftCorner)
{
    _calculateBottomVertices();
    _calculateNormalUp();
}


void ChunkPart::append(std::vector<VertexData>& vertices, std::vector<unsigned int>& indices)
{
    int startSize = vertices.size();
    _appendVertices(vertices);
    _appendFaces(startSize, indices);
}

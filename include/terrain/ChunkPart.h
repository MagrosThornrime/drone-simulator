#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <rendering/Mesh.h>

class ChunkPart
{
    bool _isUpperLeftCorner;
    glm::vec3 _upVertex1, _upVertex2, _upVertex3;
    glm::vec3 _downVertex1, _downVertex2, _downVertex3;

    float _height;

    glm::vec3 _normalUp, _normal12, _normal23, _normal13;
    const glm::vec3 _normalDown = glm::vec3(0.0f, -1.0f, 0.0f);

    const glm::vec2 _texBottomLeft = glm::vec2(0.0f, 0.0f);
    const glm::vec2 _texBottomRight = glm::vec2(1.0f, 0.0f);
    const glm::vec2 _texTopLeft = glm::vec2(0.0f, 1.0f);
    const glm::vec2 _texTopRight = glm::vec2(1.0f, 1.0f);

    void _calculateBottomVertices();
    void _calculateNormalUp();
    void _appendVertices(std::vector<VertexData>& vertices);
    void _appendFaces(int startSize, std::vector<unsigned int>& indices);

    public:
    ChunkPart(glm::vec3 upVertex1, glm::vec3 upVertex2, glm::vec3 upVertex3, float height, bool isUpperLeftCorner);
    void append(std::vector<VertexData>& vertices, std::vector<unsigned int>& indices);
};
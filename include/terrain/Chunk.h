#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <rendering/Mesh.h>

class Chunk
{
    glm::vec3 _upBackwardLeft, _upBackwardRight, _upForwardLeft, _upForwardRight;
    glm::vec3 _downBackwardLeft, _downBackwardRight, _downForwardLeft, _downForwardRight;

    glm::vec3 _normalUpForward, _normalUpBackward;
    const glm::vec3 _normalDown = glm::vec3(0.0f, -1.0f, 0.0f);
    const glm::vec3 _normalLeft = glm::vec3(-1.0f, 0.0f, 0.0f);
    const glm::vec3 _normalRight = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 _normalForward = glm::vec3(0.0f, 0.0f, 1.0f);
    const glm::vec3 _normalBackward = glm::vec3(0.0f, 0.0f, -1.0f);

    const glm::vec2 _texBackwardLeft = glm::vec2(0.0f, 0.0f);
    const glm::vec2 _texBackwardRight = glm::vec2(1.0f, 0.0f);
    const glm::vec2 _texForwardLeft = glm::vec2(0.0f, 1.0f);
    const glm::vec2 _texForwardRight = glm::vec2(1.0f, 1.0f);

    void _appendFace(glm::vec3 bottomLeft, glm::vec3 bottomRight, glm::vec3 topLeft, glm::vec3 topRight,
        glm::vec3 normalTop, glm::vec3 normalBottom, std::vector<VertexData>& vertices,
        std::vector<unsigned int>& indices);

    void _generateNormalsUp();

    public:
    Chunk(glm::vec3 upBackwardLeft, glm::vec3 upBackwardRight, glm::vec3 upForwardLeft, glm::vec3 upForwardRight,
        float minY, float maxY);
    void append(std::vector<VertexData>& vertices, std::vector<unsigned int>& indices);
};
#pragma once
#include <vector>
#include <collisions/ConvexPart.h>


class Collider
{
    const double _epsilon = 0.00001;
    std::vector<ConvexPart> _parts;
    void _removeAdjacent(const std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& result);

public:
    static bool areColliding(const Collider& collider1, const Collider& collider2);
    void addPart(const std::vector<glm::vec3>& vertices);
    void setDynamicVertices(const glm::mat4& modelMatrix, glm::vec3 scale);
};

#pragma once
#include <vector>
#include <collisions/ConvexPart.h>


class Collider
{
    std::vector<ConvexPart> _parts;

public:
    static bool areColliding(const Collider& collider1, const Collider& collider2);
    void addPart(const std::vector<glm::dvec3>& vertices);
    void setDynamicVertices(glm::dvec3 position, glm::dvec3 scale);
};

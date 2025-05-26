#include <collisions/Collider.h>

void Collider::addPart(const std::vector<glm::dvec3>& vertices)
{
    std::vector<glm::dvec3> newVertices;
    _removeAdjacent(vertices, newVertices);
    _parts.emplace_back(newVertices);
}

void Collider::setDynamicVertices(const glm::dmat4& modelMatrix, glm::dvec3 scale)
{
    for (auto& part : _parts)
    {
        part.setDynamicVertices(modelMatrix, scale);
    }
}

void Collider::_removeAdjacent(const std::vector<glm::dvec3>& vertices, std::vector<glm::dvec3>& result)
{
    result.reserve(vertices.size());
    for (auto& vertex : vertices)
    {
        bool alreadyAdded = false;
        for (auto& addedVertex : result)
        {
            if (distance(addedVertex, vertex) < _epsilon)
            {
                alreadyAdded = true;
                break;
            }
        }
        if (!alreadyAdded)
        {
            result.emplace_back(vertex);
        }
    }
}

bool Collider::areColliding(const Collider& collider1, const Collider& collider2)
{
    for (auto& part1 : collider1._parts)
    {
        for (auto& part2 : collider2._parts)
        {
            if (ConvexPart::isColliding(part1, part2))
            {
                return true;
            }
        }
    }
    return false;
}

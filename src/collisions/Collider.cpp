#include <collisions/Collider.h>

void Collider::addPart(const std::vector<glm::dvec3>& vertices)
{
    _parts.emplace_back(vertices);
}

void Collider::setDynamicVertices(glm::dvec3 position, glm::dvec3 scale)
{
    for (auto& part : _parts)
    {
        part.setDynamicVertices(position, scale);
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


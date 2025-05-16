#include <collisions/Collider.h>

void Collider::addPart(const std::vector<glm::vec3>& vertices)
{
    _parts.emplace_back(vertices);
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


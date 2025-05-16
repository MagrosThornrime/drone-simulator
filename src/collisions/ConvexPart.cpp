#include <collisions/ConvexPart.h>
#include <glm/geometric.hpp>

std::pair<glm::vec3, float> ConvexPart::_farthestPoint(glm::vec3 referencePoint) const
{
    float maxDistance = 0.0f;
    glm::vec3 maxPoint = referencePoint;
    for (auto point : _vertices)
    {
        float distance = glm::distance(point, referencePoint);
        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxPoint = point;
        }
    }
    return std::pair(maxPoint, maxDistance);
}


void ConvexPart::_findSphere()
{
    glm::vec3 initialPoint = _vertices[0];
    glm::vec3 constructingPoint1 = _farthestPoint(initialPoint).first;
    auto searchResult = _farthestPoint(constructingPoint1);
    glm::vec3 constructionPoint2 = searchResult.first;
    float constructingDistance = searchResult.second;

    _sphereCenter = (constructingPoint1 + constructionPoint2) / 2.0f;
    _sphereRadius = constructingDistance / 2;

    for (auto point : _vertices)
    {
        float distance = glm::distance(point, _sphereCenter);
        if (distance > _sphereRadius)
        {
            _sphereRadius = (_sphereRadius + distance) / 2.0f;
            float factor = _sphereRadius / distance;
            _sphereCenter = point - distance * factor;
        }
    }
}


ConvexPart::ConvexPart(const std::vector<glm::vec3>& vertices) : _vertices(vertices) {
    _findSphere();
}


bool ConvexPart::_isSphereColliding(const ConvexPart& part1, const ConvexPart& part2)
{
    const float distance = glm::distance(part1._sphereCenter, part2._sphereCenter);
    return distance < part1._sphereRadius + part2._sphereRadius;
}


bool ConvexPart::isColliding(const ConvexPart& part1, const ConvexPart& part2)
{
    return _isSphereColliding(part1, part2);
}

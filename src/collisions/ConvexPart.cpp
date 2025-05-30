#include <collisions/ConvexPart.h>
#include <glm/geometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <collisions/GJK.h>


std::pair<glm::vec3, float> ConvexPart::_farthestPoint(glm::vec3 referencePoint) const
{
    float maxDistance = 0.0f;
    glm::vec3 maxPoint = referencePoint;
    for (auto point : _staticVertices)
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
    glm::vec3 initialPoint = _staticVertices[0];
    glm::vec3 constructingPoint1 = _farthestPoint(initialPoint).first;
    auto searchResult = _farthestPoint(constructingPoint1);
    glm::vec3 constructionPoint2 = searchResult.first;
    float constructingDistance = searchResult.second;

    _staticSphereCenter = (constructingPoint1 + constructionPoint2) / 2.0f;
    _staticSphereRadius = constructingDistance / 2.0f;

    for (auto point : _staticVertices)
    {
        float distance = glm::distance(point, _staticSphereCenter);
        if (distance > _staticSphereRadius)
        {
            _staticSphereRadius = (_staticSphereRadius + distance) / 2.0f;
            float factor = _staticSphereRadius / distance;
            _staticSphereCenter = glm::mix(_staticSphereCenter, point, 1.0f - factor);
        }
    }
}


ConvexPart::ConvexPart(const std::vector<glm::vec3>& vertices) : _staticVertices(vertices) {
    _findSphere();
    _dynamicVertices = _staticVertices;
}


bool ConvexPart::_isSphereColliding(const ConvexPart& part1, const ConvexPart& part2)
{
    const float distance = glm::distance(part1._dynamicSphereCenter, part2._dynamicSphereCenter);
    return distance < part1._dynamicSphereRadius + part2._dynamicSphereRadius;
}

void ConvexPart::setDynamicVertices(const glm::mat4& modelMatrix, glm::vec3 scale)
{

    for (int i = 0; i < _staticVertices.size(); i++)
    {
        _dynamicVertices[i] = glm::vec3(modelMatrix * glm::dvec4(_staticVertices[i], 1.0f));
    }
    _dynamicSphereCenter = glm::vec3(modelMatrix * glm::dvec4(_staticSphereCenter, 1.0f));
    _dynamicSphereRadius = _staticSphereRadius * glm::length(scale);
}


bool ConvexPart::isColliding(const ConvexPart& part1, const ConvexPart& part2)
{
    if (!_isSphereColliding(part1, part2))
    {
        return false;
    }
    return isCollidingGJK(part1._dynamicVertices, part2._dynamicVertices);
}

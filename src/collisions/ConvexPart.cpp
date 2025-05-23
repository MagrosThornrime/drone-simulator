#include <collisions/ConvexPart.h>
#include <glm/geometric.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <collisions/GJK.h>


std::pair<glm::dvec3, double> ConvexPart::_farthestPoint(glm::dvec3 referencePoint) const
{
    double maxDistance = 0.0;
    glm::dvec3 maxPoint = referencePoint;
    for (auto point : _staticVertices)
    {
        double distance = glm::distance(point, referencePoint);
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
    glm::dvec3 initialPoint = _staticVertices[0];
    glm::dvec3 constructingPoint1 = _farthestPoint(initialPoint).first;
    auto searchResult = _farthestPoint(constructingPoint1);
    glm::dvec3 constructionPoint2 = searchResult.first;
    double constructingDistance = searchResult.second;

    _staticSphereCenter = (constructingPoint1 + constructionPoint2) / 2.0;
    _staticSphereRadius = constructingDistance / 2.0;

    for (auto point : _staticVertices)
    {
        double distance = glm::distance(point, _staticSphereCenter);
        if (distance > _staticSphereRadius)
        {
            _staticSphereRadius = (_staticSphereRadius + distance) / 2.0;
            double factor = _staticSphereRadius / distance;
            _staticSphereCenter = glm::mix(_staticSphereCenter, point, 1.0 - factor);
        }
    }
}


ConvexPart::ConvexPart(const std::vector<glm::dvec3>& vertices) : _staticVertices(vertices) {
    _findSphere();
    _dynamicVertices = _staticVertices;
}


bool ConvexPart::_isSphereColliding(const ConvexPart& part1, const ConvexPart& part2)
{
    const double distance = glm::distance(part1._dynamicSphereCenter, part2._dynamicSphereCenter);
    return distance < part1._dynamicSphereRadius + part2._dynamicSphereRadius;
}

void ConvexPart::setDynamicVertices(glm::dvec3 position, glm::dvec3 scale)
{
    auto model = glm::dmat4(1.0);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    for (int i = 0; i < _staticVertices.size(); i++)
    {
        _dynamicVertices[i] = glm::dvec3(model * glm::dvec4(_staticVertices[i], 1.0));
    }
    _dynamicSphereCenter = glm::dvec3(model * glm::dvec4(_staticSphereCenter, 1.0));
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

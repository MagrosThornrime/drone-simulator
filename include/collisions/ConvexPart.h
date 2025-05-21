#pragma once
#include <vector>
#include <glm/glm.hpp>

class ConvexPart
{
    std::vector<glm::dvec3> _staticVertices;
    glm::dvec3 _staticSphereCenter;
    double _staticSphereRadius;

    std::vector<glm::dvec3> _dynamicVertices;
    glm::dvec3 _dynamicSphereCenter;
    double _dynamicSphereRadius;

    std::pair<glm::dvec3, double> _farthestPoint(glm::dvec3 point) const;
    void _findSphere();
    static bool _isSphereColliding(const ConvexPart& part1, const ConvexPart& part2);

public:

    void setDynamicVertices(glm::dvec3 position, glm::dvec3 scale);

    explicit ConvexPart(const std::vector<glm::dvec3>& vertices);
    static bool isColliding(const ConvexPart& part1, const ConvexPart& part2);
};

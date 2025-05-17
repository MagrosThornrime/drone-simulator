#pragma once
#include <vector>
#include <glm/glm.hpp>

class ConvexPart
{
    std::vector<glm::vec3> _staticVertices;
    glm::vec3 _staticSphereCenter;
    float _staticSphereRadius;

    std::vector<glm::vec3> _dynamicVertices;
    glm::vec3 _dynamicSphereCenter;
    float _dynamicSphereRadius;

    std::pair<glm::vec3, float> _farthestPoint(glm::vec3 point) const;
    void _findSphere();
    static bool _isSphereColliding(const ConvexPart& part1, const ConvexPart& part2);

public:

    void setDynamicVertices(glm::vec3 position, glm::vec3 scale);

    explicit ConvexPart(const std::vector<glm::vec3>& vertices);
    static bool isColliding(const ConvexPart& part1, const ConvexPart& part2);
};

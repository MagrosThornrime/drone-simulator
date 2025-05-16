#pragma once
#include <vector>
#include <glm/vec3.hpp>

class ConvexPart
{
    std::vector<glm::vec3> _vertices;
    glm::vec3 _sphereCenter;
    float _sphereRadius;

    std::pair<glm::vec3, float> _farthestPoint(glm::vec3 point) const;
    void _findSphere();
    static bool _isSphereColliding(const ConvexPart& part1, const ConvexPart& part2);

public:


    explicit ConvexPart(const std::vector<glm::vec3>& vertices);
    static bool isColliding(const ConvexPart& part1, const ConvexPart& part2);
};

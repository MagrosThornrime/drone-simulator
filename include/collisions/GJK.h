#pragma once
#include <glm/glm.hpp>
#include <vector>

const float EPSILON = 0.0;

glm::vec3 supportFunction(const std::vector<glm::vec3>& shape, glm::vec3 direction);

glm::vec3 minkowskiPoint(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2,
						glm::vec3 direction);

bool pointPassedOrigin(glm::vec3 direction, glm::vec3 supportVertex);

bool createLine(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
				const std::vector<glm::vec3>& shape2);

bool createTriangle(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
					const std::vector<glm::vec3>& shape2);

bool createTetrahedron(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
					const std::vector<glm::vec3>& shape2);

bool containsOriginTetrahedron(std::vector<glm::vec3>& simplex);


bool isCollidingGJK(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2, int maxIterations=10000);
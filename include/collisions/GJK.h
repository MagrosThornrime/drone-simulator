#pragma once
#include <glm/glm.hpp>
#include <vector>

const double EPSILON = 0.0;

glm::dvec3 supportFunction(const std::vector<glm::dvec3>& shape, glm::dvec3 direction);

glm::dvec3 minkowskiPoint(const std::vector<glm::dvec3>& shape1, const std::vector<glm::dvec3>& shape2,
						glm::dvec3 direction);

bool pointPassedOrigin(glm::dvec3 direction, glm::dvec3 supportVertex);

bool createLine(std::vector<glm::dvec3>& simplex, const std::vector<glm::dvec3>& shape1,
				const std::vector<glm::dvec3>& shape2);

bool createTriangle(std::vector<glm::dvec3>& simplex, const std::vector<glm::dvec3>& shape1,
					const std::vector<glm::dvec3>& shape2);

bool createTetrahedron(std::vector<glm::dvec3>& simplex, const std::vector<glm::dvec3>& shape1,
					const std::vector<glm::dvec3>& shape2);

bool containsOriginTetrahedron(std::vector<glm::dvec3>& simplex);


bool isCollidingGJK(const std::vector<glm::dvec3>& shape1, const std::vector<glm::dvec3>& shape2, int maxIterations=10000);
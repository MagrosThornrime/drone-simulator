#include <iostream>
#include <collisions/GJK.h>
#include <limits>
#include <string>

#include "Logger.h"


glm::vec3 supportFunction(const std::vector<glm::vec3>& shape, glm::vec3 direction) {

	float supportProduct = std::numeric_limits<float>::lowest();
	glm::vec3 supportVertex(0.0f);

	for (auto vertex : shape)
	{
		const float product = dot(vertex, direction);
		if (product > supportProduct) {
			supportProduct = product;
			supportVertex = vertex;
		}
	}
	return supportVertex;
}

glm::vec3 minkowskiPoint(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2,
						glm::vec3 direction) {
	glm::vec3 minkowski1 = supportFunction(shape1, direction);
	glm::vec3 minkowski2 = supportFunction(shape2, -direction);
	return minkowski1 - minkowski2;
}

bool pointPassedOrigin(glm::vec3 direction, glm::vec3 supportVertex){
	return dot(supportVertex, direction) > 0.0f;
}

bool createLine(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
				const std::vector<glm::vec3>& shape2){
	glm::vec3 direction = normalize(-simplex.back());
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool createTriangle(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
					const std::vector<glm::vec3>& shape2){
	glm::vec3 A = simplex[0];
	glm::vec3 B = simplex[1];
	glm::vec3 AB = B - A;
	glm::vec3 A0 = -A;
	glm::vec3 direction = normalize(cross(cross(AB, A0), AB));
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool createTetrahedron(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
						const std::vector<glm::vec3>& shape2)
{
	glm::vec3 A = simplex[0];
	glm::vec3 B = simplex[1];
	glm::vec3 C = simplex[2];
	glm::vec3 BA = B - A;
	glm::vec3 CA = C - A;
	glm::vec3 A0 = -A;
	glm::vec3 direction = normalize(cross(BA, CA));
	if (dot(direction, A0) < 0.0f)
	{
		direction *= -1.0f;
	}
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool containsOriginTetrahedron(std::vector<glm::vec3>& simplex){
	glm::vec3 A = simplex[0];
	glm::vec3 B = simplex[1];
	glm::vec3 C = simplex[2];
	glm::vec3 D = simplex[3];
	glm::vec3 AD = D - A;
	glm::vec3 BD = D - B;
	glm::vec3 CD = D - C;
	glm::vec3 DO = -D;

	glm::vec3 normalABD = normalize(cross(AD, BD));
	if (dot(normalABD, -CD) > 0.0f)
	{
		normalABD *= -1.0f;
	}
	if (dot(normalABD, DO) > -EPSILON){
		simplex.erase(simplex.begin() + 2);
		return false;
	}
	glm::vec3 normalBCD = normalize(cross(BD, CD));
	if (dot(normalBCD, -AD) > 0.0f)
	{
		normalBCD *= -1.0f;
	}
	if (dot(normalBCD, DO) > -EPSILON){
		simplex.erase(simplex.begin());
		return false;
	}
	glm::vec3 normalACD = normalize(cross(CD, AD));
	if (dot(normalACD, -BD) > 0.0f)
	{
		normalACD *= -1.0f;
	}
	if (dot(normalACD, DO) > -EPSILON){
		simplex.erase(simplex.begin() + 1);
		return false;
	}
	return true;
}

bool isCollidingGJK(const std::vector<glm::vec3>& shape1, const std::vector<glm::vec3>& shape2,
	int maxIterations) {

	std::vector<glm::vec3> simplex;
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));

	if (!createLine(simplex, shape1, shape2)){
		return false;
	}
	if (!createTriangle(simplex, shape1, shape2)){
		return false;
	}
	if (!createTetrahedron(simplex, shape1, shape2))
	{
		return false;
	}
	int iterations = 0;
	while (!containsOriginTetrahedron(simplex)){
		if (iterations > maxIterations)
		{
			return false;
		}
		if (!createTetrahedron(simplex, shape1, shape2))
		{
			return false;
		}
		iterations++;
	}
	return true;
}
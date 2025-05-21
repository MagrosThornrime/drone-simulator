#include <iostream>
#include <collisions/GJK.h>
#include <limits>
#include <string>

#include "Logger.h"


glm::dvec3 supportFunction(const std::vector<glm::dvec3>& shape, glm::dvec3 direction) {

	float supportProduct = std::numeric_limits<float>::lowest();
	glm::dvec3 supportVertex(0.0f);

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

glm::dvec3 minkowskiPoint(const std::vector<glm::dvec3>& shape1, const std::vector<glm::dvec3>& shape2,
						glm::dvec3 direction) {
	glm::dvec3 minkowski1 = supportFunction(shape1, direction);
	glm::dvec3 minkowski2 = supportFunction(shape2, -direction);
	return minkowski1 - minkowski2;
}

bool pointPassedOrigin(glm::dvec3 direction, glm::dvec3 supportVertex){
	return dot(supportVertex, direction) > 0.0f;
}

bool createLine(std::vector<glm::dvec3>& simplex, const std::vector<glm::dvec3>& shape1,
				const std::vector<glm::dvec3>& shape2){
	glm::dvec3 direction = normalize(-simplex.back());
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool createTriangle(std::vector<glm::dvec3>& simplex, const std::vector<glm::dvec3>& shape1,
					const std::vector<glm::dvec3>& shape2){
	glm::dvec3 lineVector = simplex[1] - simplex[0];
	glm::dvec3 towardsOrigin = -simplex[0];
	glm::dvec3 direction = normalize(cross(cross(lineVector, towardsOrigin), lineVector));
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool createTetrahedron(std::vector<glm::dvec3>& simplex, const std::vector<glm::dvec3>& shape1,
						const std::vector<glm::dvec3>& shape2)
{
	glm::dvec3 lineVector1 = simplex[1] - simplex[0];
	glm::dvec3 lineVector2 = simplex[2] - simplex[0];
	glm::dvec3 towardsOrigin = -simplex[0];
	glm::dvec3 direction = normalize(cross(lineVector1, lineVector2));
	if (dot(direction, towardsOrigin) < 0.0f)
	{
		direction *= -1.0f;
	}
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool containsOriginTetrahedron(std::vector<glm::dvec3>& simplex){
	glm::dvec3 A = simplex[0];
	glm::dvec3 B = simplex[1];
	glm::dvec3 C = simplex[2];
	glm::dvec3 D = simplex[3];
	glm::dvec3 AD = D - A;
	glm::dvec3 BD = D - B;
	glm::dvec3 CD = D - C;
	glm::dvec3 DO = -D;

	glm::dvec3 normalABD = normalize(cross(AD, BD));
	if (dot(normalABD, -CD) > 0.0f)
	{
		normalABD *= -1.0f;
	}
	if (dot(normalABD, DO) > -EPSILON){
		simplex.erase(simplex.begin() + 2);
		return false;
	}
	glm::dvec3 normalBCD = normalize(cross(BD, CD));
	if (dot(normalBCD, -AD) > 0.0f)
	{
		normalBCD *= -1.0f;
	}
	if (dot(normalBCD, DO) > -EPSILON){
		simplex.erase(simplex.begin());
		return false;
	}
	glm::dvec3 normalACD = normalize(cross(CD, AD));
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

bool containsOriginTriangle(std::vector<glm::dvec3>& simplex){
	glm::dvec3 A = simplex[0];
	glm::dvec3 B = simplex[1];
	glm::dvec3 C = simplex[2];
	glm::dvec3 CA = A - C;
	glm::dvec3 CB = B - C;
	glm::dvec3 CO = -C;

	glm::dvec3 normalCA = normalize(cross(cross(CA, CB), CB));

	if(dot(normalCA, CO) > -EPSILON){
		simplex.erase(simplex.begin());
		return false;
	}
	glm::dvec3 normalCB = normalize(cross(cross(CB, CA), CA));
	if(dot(normalCB, CO) > -EPSILON){
		simplex.erase(simplex.begin() + 1);
		return false;
	}

	return true;
}

bool isCollidingGJK(const std::vector<glm::dvec3>& shape1, const std::vector<glm::dvec3>& shape2,
	int maxIterations) {

	std::vector<glm::dvec3> simplex;
	glm::dvec3 direction = glm::dvec3(0.0f, 0.0f, 1.0f);
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
	while (!containsOriginTetrahedron(simplex) && !containsOriginTriangle(simplex)){
		if (iterations > maxIterations)
		{
			return false;
		}
		if (!createTetrahedron(simplex, shape1, shape2))
		{
			return false;
		}
		if (!createTriangle(simplex, shape1, shape2))
		iterations++;
	}

	Logger::log("1", info);
	for (auto vertex : shape1)
	{
		std::cout << "[" + std::to_string(vertex.x) + ", " + std::to_string(vertex.y) + ", " + std::to_string(vertex.z) + "]," << std::endl;
	}
	Logger::log("2", info);
	for (auto vertex : shape2)
	{
		std::cout << "[" + std::to_string(vertex.x) + ", " + std::to_string(vertex.y) + ", " + std::to_string(vertex.z) + "]," << std::endl;
	}

	return true;
}
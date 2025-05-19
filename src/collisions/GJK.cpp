#include <collisions/GJK.h>
#include <limits>
#include <bits/stdc++.h>


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
	glm::vec3 direction = -simplex.back();
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool createTriangle(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
					const std::vector<glm::vec3>& shape2){
	glm::vec3 lineVector = simplex[1] - simplex[0];
	glm::vec3 towardsOrigin = -simplex[0];
	glm::vec3 direction = cross(cross(lineVector, towardsOrigin), lineVector);
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool createTetrahedron(std::vector<glm::vec3>& simplex, const std::vector<glm::vec3>& shape1,
						const std::vector<glm::vec3>& shape2)
{
	glm::vec3 lineVector1 = simplex[1] - simplex[0];
	glm::vec3 lineVector2 = simplex[2] - simplex[0];
	glm::vec3 towardsOrigin = -simplex[0];
	glm::vec3 direction = cross(lineVector1, lineVector2);
	if (dot(direction, towardsOrigin) < 0.0f)
	{
		direction *= -1.0f;
	}
	simplex.push_back(minkowskiPoint(shape1, shape2, direction));
	return pointPassedOrigin(direction, simplex.back());
}

bool containsOrigin(std::vector<glm::vec3>& simplex){
	glm::vec3 lineVector1 = simplex[3] - simplex[0];
	glm::vec3 lineVector2 = simplex[3] - simplex[1];
	glm::vec3 lineVector3 = simplex[3] - simplex[2];
	glm::vec3 towardsOrigin = -simplex[3];

	glm::vec3 perpendicular1 = cross(lineVector1, lineVector2);
	if (dot(perpendicular1, towardsOrigin) > 0.0f){
		simplex.erase(std::ranges::remove(simplex, simplex[2]).begin(), simplex.end());
		return false;
	}
	glm::vec3 perpendicular2 = cross(lineVector2, lineVector3);
	if (dot(perpendicular2, towardsOrigin) > 0.0f){
		simplex.erase(std::ranges::remove(simplex, simplex[0]).begin(), simplex.end());
		return false;
	}
	glm::vec3 perpendicular3 = cross(lineVector3, lineVector1);
	if (dot(perpendicular3, towardsOrigin) > 0.0f){
		simplex.erase(std::ranges::remove(simplex, simplex[1]).begin(), simplex.end());
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
	while (!containsOrigin(simplex) && iterations < maxIterations){
		if (!createTetrahedron(simplex, shape1, shape2)){
			return false;
		}
	}
	return true;
}
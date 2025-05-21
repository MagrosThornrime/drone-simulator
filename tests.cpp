#include <gtest/gtest.h>
#include <collisions/GJK.h>

TEST(CollisionTests, CubeAndTetrahedron)
{
    std::vector<glm::dvec3> cube1 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::dvec3> tetra1 = {
        { 0.0f,  0.0f,  0.0f},
        { 1.0f,  0.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f},
        { 0.0f,  0.0f,  1.0f}
    };

    ASSERT_TRUE(isCollidingGJK(cube1, tetra1));
}

TEST(CollisionTests, TwoOverlappingCubes)
{
    std::vector<glm::dvec3> cube2 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::dvec3> cube3 = {
        { 0.3f, -0.5f, -0.5f},
        { 1.3f, -0.5f, -0.5f},
        { 1.3f,  0.5f, -0.5f},
        { 0.3f,  0.5f, -0.5f},
        { 0.3f, -0.5f,  0.5f},
        { 1.3f, -0.5f,  0.5f},
        { 1.3f,  0.5f,  0.5f},
        { 0.3f,  0.5f,  0.5f}
    };

    ASSERT_TRUE(isCollidingGJK(cube2, cube3));
}

TEST(CollisionTests, TetrahedronCubeCorner)
{
    std::vector<glm::dvec3> cube4 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::dvec3> tetra2 = {
        { 0.4f, 0.4f, 0.4f},
        { 1.0f, 0.4f, 0.4f},
        { 0.4f, 1.0f, 0.4f},
        { 0.4f, 0.4f, 1.0f}
    };

    ASSERT_TRUE(isCollidingGJK(cube4, tetra2));
}

TEST(CollisionTests, TetrahedronOutsideCube)
{
    std::vector<glm::dvec3> cube5 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::dvec3> tetra3 = {
        { 2.0f, 2.0f, 2.0f},
        { 3.0f, 2.0f, 2.0f},
        { 2.0f, 3.0f, 2.0f},
        { 2.0f, 2.0f, 3.0f}
    };

    ASSERT_FALSE(isCollidingGJK(cube5, tetra3));
}

TEST(CollisionTests, TwoSeparatedCubes)
{
    std::vector<glm::dvec3> cube6 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::dvec3> cube7 = {
        { 2.0f, 2.0f, 2.0f},
        { 3.0f, 2.0f, 2.0f},
        { 3.0f, 3.0f, 2.0f},
        { 2.0f, 3.0f, 2.0f},
        { 2.0f, 2.0f, 3.0f},
        { 3.0f, 2.0f, 3.0f},
        { 3.0f, 3.0f, 3.0f},
        { 2.0f, 3.0f, 3.0f}
    };

    ASSERT_FALSE(isCollidingGJK(cube6, cube7));
}

TEST(CollisionTests, TetrahedronCloseToCube)
{
    std::vector<glm::dvec3> cube8 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::dvec3> tetra4 = {
        { 1.1f, 1.1f, 1.1f},
        { 2.0f, 1.1f, 1.1f},
        { 1.1f, 2.0f, 1.1f},
        { 1.1f, 1.1f, 2.0f}
    };
    ASSERT_FALSE(isCollidingGJK(cube8, tetra4));
}

TEST(CollisionTests, Prisms)
{
    std::vector<glm::dvec3> hexPrism = {
        // Bottom hexagon (z = -0.5)
        { 1.0f,  0.0f, -0.5f},
        { 0.5f,  0.866f, -0.5f},
        {-0.5f,  0.866f, -0.5f},
        {-1.0f,  0.0f, -0.5f},
        {-0.5f, -0.866f, -0.5f},
        { 0.5f, -0.866f, -0.5f},

        // Top hexagon (z = 0.5)
        { 1.0f,  0.0f, 0.5f},
        { 0.5f,  0.866f, 0.5f},
        {-0.5f,  0.866f, 0.5f},
        {-1.0f,  0.0f, 0.5f},
        {-0.5f, -0.866f, 0.5f},
        { 0.5f, -0.866f, 0.5f}
    };

    std::vector<glm::dvec3> triPrism = {
        // Base triangle (z = -0.3)
        { 0.2f,  0.0f, -0.3f},
        { 1.2f,  0.0f, -0.3f},
        { 0.7f,  1.0f, -0.3f},

        // Top triangle (z = 0.7)
        { 0.2f,  0.0f, 0.7f},
        { 1.2f,  0.0f, 0.7f},
        { 0.7f,  1.0f, 0.7f}
    };

    ASSERT_TRUE(isCollidingGJK(hexPrism, triPrism));
}

TEST(CollisionTests, Sus)
{
    std::vector<glm::dvec3> boxVertices = {
        glm::dvec3(-58.210522f, 2880.000000f, -120.029091f),
        glm::dvec3(181.789474f, 2880.000000f, -120.029091f),
        glm::dvec3(181.789474f, 3120.000000f, -120.029091f),
        glm::dvec3(-58.210522f, 3120.000000f, -120.029091f),
        glm::dvec3(-58.210522f, 2880.000000f, 119.970909f),
        glm::dvec3(181.789474f, 2880.000000f, 119.970909f),
        glm::dvec3(181.789474f, 3120.000000f, 119.970909f),
        glm::dvec3(-58.210522f, 3120.000000f, 119.970909f)
    };

    std::vector<glm::dvec3> tetrahedronVertices = {
        glm::dvec3(500.000000f, 3100.000000f, 100.000000f),
        glm::dvec3(300.000000f, 2900.000000f, 100.000000f),
        glm::dvec3(300.000000f, 3100.000000f, -100.000000f),
        glm::dvec3(500.000000f, 2900.000000f, -100.000000f)
    };

    ASSERT_TRUE(isCollidingGJK(boxVertices, tetrahedronVertices));
}
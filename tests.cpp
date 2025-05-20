#include <gtest/gtest.h>
#include <collisions/GJK.h>

TEST(Tests, CubeAndTetrahedron)
{
    std::vector<glm::vec3> cube1 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::vec3> tetra1 = {
        { 0.0f,  0.0f,  0.0f},
        { 1.0f,  0.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f},
        { 0.0f,  0.0f,  1.0f}
    };

    ASSERT_TRUE(isCollidingGJK(cube1, tetra1));
}

TEST(Tests, TwoOverlappingCubes)
{
    std::vector<glm::vec3> cube2 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::vec3> cube3 = {
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

TEST(Tests, TetrahedronCubeCorner)
{
    std::vector<glm::vec3> cube4 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::vec3> tetra2 = {
        { 0.4f, 0.4f, 0.4f},
        { 1.0f, 0.4f, 0.4f},
        { 0.4f, 1.0f, 0.4f},
        { 0.4f, 0.4f, 1.0f}
    };

    ASSERT_TRUE(isCollidingGJK(cube4, tetra2));
}

TEST(Tests, TetrahedronOutsideCube)
{
    std::vector<glm::vec3> cube5 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::vec3> tetra3 = {
        { 2.0f, 2.0f, 2.0f},
        { 3.0f, 2.0f, 2.0f},
        { 2.0f, 3.0f, 2.0f},
        { 2.0f, 2.0f, 3.0f}
    };

    ASSERT_FALSE(isCollidingGJK(cube5, tetra3));
}

TEST(Tests, TwoSeparatedCubes)
{
    std::vector<glm::vec3> cube6 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::vec3> cube7 = {
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

TEST(Tests, TetrahedronCloseToCube)
{
    std::vector<glm::vec3> cube8 = {
        {-0.5f, -0.5f, -0.5f},
        { 0.5f, -0.5f, -0.5f},
        { 0.5f,  0.5f, -0.5f},
        {-0.5f,  0.5f, -0.5f},
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f,  0.5f,  0.5f},
        {-0.5f,  0.5f,  0.5f}
    };

    std::vector<glm::vec3> tetra4 = {
        { 1.1f, 1.1f, 1.1f},
        { 2.0f, 1.1f, 1.1f},
        { 1.1f, 2.0f, 1.1f},
        { 1.1f, 1.1f, 2.0f}
    };
    ASSERT_FALSE(isCollidingGJK(cube8, tetra4));
}

TEST(Tests, Prisms)
{
    std::vector<glm::vec3> hexPrism = {
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

    std::vector<glm::vec3> triPrism = {
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
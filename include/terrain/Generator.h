#pragma once
#include <memory>
#include <terrain/Noise.h>
#include <rendering/Mesh.h>

class Generator
{
    std::shared_ptr<Noise> _noise;
    Mesh _generateMesh(int size, const std::string& texturePath, const std::string& textureType);
    void _generateSquareChunk(float x, float z, float size, std::vector<VertexData>& vertices,
        std::vector<unsigned int>& indices);
    glm::vec3 _generateVertex(float x, float z, float size);
    glm::vec3 _generateNormal(glm::vec3 edge, glm::vec3 diagonal);

public:
    int octaves = 2;
    float amplitude = 0.4f;
    float frequency = 0.005f;
    float amplitudeFactor = 0.5f;
    float frequencyFactor = 2.0f;
    std::string texturePath = "assets/images/grass.png";
    std::string textureType = "texture_diffuse";
    std::string textureName = "grass";

    Generator(int permutationSize, int seed);
    explicit Generator(int permutationSize);

    void generateTerrain(const std::string& name, int size);
};

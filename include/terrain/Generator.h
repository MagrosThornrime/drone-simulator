#pragma once
#include <memory>
#include <terrain/Noise.h>

#include "rendering/Mesh.h"

class Generator
{
    std::shared_ptr<Noise> _noise;
    Mesh _generateMesh(int width, int height, const std::string& texturePath,
                                const std::string& textureType);
    void _generateSquareChunk(int x, int z, std::vector<VertexData>& vertices,
        std::vector<unsigned int>& indices);
    glm::vec3 _generateVertex(int x, int z);
    glm::vec3 _generateNormal(glm::vec3 edge, glm::vec3 diagonal);

public:
    int octaves = 1;
    float amplitude = 1.0f;
    float frequency = 0.005f;
    float amplitudeFactor = 0.5f;
    float frequencyFactor = 2.0f;
    float maxHeight = 100.0f;
    std::string texturePath = "assets/images/grass.png";
    std::string textureType = "texture_diffuse";
    std::string textureName = "grass";

    Generator(int permutationSize, int seed);
    explicit Generator(int permutationSize);

    void generateTerrain(const std::string& name, int width, int height);
};

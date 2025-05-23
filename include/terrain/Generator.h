#pragma once
#include <memory>
#include <terrain/Noise.h>
#include <rendering/Mesh.h>
#include <resources/AssetManager.h>

class Generator
{
    std::shared_ptr<Noise> _noise;
    void _generateChunk(float x, float z, int size, const std::string& texturePath, const std::string& textureType,
        Texture* texture, Model* model);
    glm::vec3 _generateVertex(float x, float z, float size);
    glm::vec3 _generateNormal(glm::vec3 edge, glm::vec3 diagonal);

public:
    int octaves = 6;
    float amplitude = 0.6f;
    float frequency = 0.005f;
    float amplitudeFactor = 0.5f;
    float frequencyFactor = 2.0f;
    float minY = -1.0f;
    float maxY = 1.0f;
    float chunkHeight = 0.1f;
    std::string texturePath = "assets/images/grass.png";
    std::string textureType = "texture_diffuse";
    std::string textureName = "grass";

    Generator(int permutationSize, float offsetMin, float offsetMax, int seed);
    Generator(int permutationSize, float offsetMin, float offsetMax);

    void generateTerrain(AssetManager& assetManager, const std::string& name, int size);
};

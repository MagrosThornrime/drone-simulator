#include <iostream>
#include <terrain/Generator.h>
#include <resources/AssetManager.h>
#include <terrain/ChunkPart.h>

Generator::Generator(int permutationSize, float offsetMin, float offsetMax)
{
    _noise = std::make_shared<Noise>(permutationSize, offsetMin, offsetMax);
    Logger::log("Terrain generator created", info);
}


Generator::Generator(int permutationSize, float offsetMin, float offsetMax, int seed)
{
    _noise = std::make_shared<Noise>(permutationSize, offsetMin, offsetMax, seed);
    Logger::log("Terrain generator created", info);
}

void Generator::_generateChunk(float x, float z, int size, const std::string& texturePath,
                            const std::string& textureType, Texture* texture, Model* model)
{
    glm::vec3 bottomLeft = _generateVertex(x, z, size);
    glm::vec3 bottomRight = _generateVertex(x + 1.0f, z, size);
    glm::vec3 topLeft = _generateVertex(x, z + 1.0f, size);
    glm::vec3 topRight = _generateVertex(x + 1.0f, z + 1.0f, size);

    std::vector<VertexData> vertices1, vertices2;
    std::vector<unsigned int> indices1, indices2;
    ChunkPart part1(bottomLeft, topLeft, topRight, chunkHeight, true);
    ChunkPart part2(topRight, bottomRight, bottomLeft, chunkHeight, false);
    part1.append(vertices1, indices1);
    part2.append(vertices2, indices2);
    model->meshes.emplace_back(Mesh(vertices1, indices1, {texturePath}, {textureType}));
    model->meshes.back().textures.push_back(texture);
    model->meshes.emplace_back(Mesh(vertices2, indices2, {texturePath}, {textureType}));
    model->meshes.back().textures.push_back(texture);
}

glm::vec3 Generator::_generateVertex(float x, float z, float size)
{
    float y = _noise->generate(x, z, octaves, amplitude, frequency,
                               amplitudeFactor, frequencyFactor, minY, maxY);
    x = x * 2.0f / size - 1.0f;
    z = z * 2.0f / size - 1.0f;
    return glm::vec3(x, y, z);
}

glm::vec3 Generator::_generateNormal(glm::vec3 edge, glm::vec3 diagonal)
{
    glm::vec3 candidate1 = glm::cross(edge, diagonal);
    glm::vec3 candidate2 = glm::cross(diagonal, edge);
    return candidate1.y > 0 ? glm::normalize(candidate1) : glm::normalize(candidate2);
}


void Generator::generateTerrain(AssetManager& assetManager, const std::string& name, int size)
{
    Model* model = assetManager.createEmptyModel(name);
    if (!assetManager.hasTexture(name))
    {
        assetManager.loadTexture(texturePath, true, textureType, textureName);
    }
    Texture* texture = assetManager.getTexture(textureName);
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            _generateChunk(x, y, size, texturePath, textureType, texture, model);
        }
    }
    // model->normalize();
    Logger::log("Terrain generated", info);
}

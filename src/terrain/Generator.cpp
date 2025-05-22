#include <iostream>
#include <terrain/Generator.h>
#include <resources/AssetManager.h>

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

Mesh Generator::_generateMesh(float x, float y, int size, const std::string& texturePath,
                            const std::string& textureType)
{
    std::vector<VertexData> vertices;
    std::vector<unsigned int> indices;

    _createAndAddChunk(x, y, size, vertices, indices);
    return Mesh(vertices, indices, {texturePath}, {textureType});
}

void Generator::_createAndAddChunk(float x, float z, float size, std::vector<VertexData>& vertices,
    std::vector<unsigned int>& indices)
{
    glm::vec3 backwardLeft = _generateVertex(x, z, size);
    glm::vec3 backwardRight = _generateVertex(x + 1.0f, z, size);
    glm::vec3 forwardLeft = _generateVertex(x, z + 1.0f, size);
    glm::vec3 forwardRight = _generateVertex(x + 1.0f, z + 1.0f, size);

    Chunk chunk(backwardLeft, backwardRight, forwardLeft,
        forwardRight, minY, maxY);
    chunk.append(vertices, indices);
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
            model->meshes.push_back(_generateMesh(x, y, size, texturePath, textureType));
            model->meshes.back().textures.push_back(texture);
        }
    }
    model->normalize();
    Logger::log("Terrain generated", info);
}

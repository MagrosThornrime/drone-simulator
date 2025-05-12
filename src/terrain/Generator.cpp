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

Mesh Generator::_generateMesh(int size, const std::string& texturePath,
                            const std::string& textureType)
{
    std::vector<VertexData> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            _generateSquareChunk(x, y, size, vertices, indices);
        }
    }
    return Mesh(vertices, indices, {texturePath}, {textureType});
}

void Generator::_generateSquareChunk(float x, float z, float size, std::vector<VertexData>& vertices,
    std::vector<unsigned int>& indices)
{
    int currentVertices = vertices.size();
    glm::vec3 bottomLeft = _generateVertex(x, z, size);
    glm::vec3 bottomRight = _generateVertex(x + 1, z, size);
    glm::vec3 topLeft = _generateVertex(x, z + 1, size);
    glm::vec3 topRight = _generateVertex(x + 1, z + 1, size);

    glm::vec3 leftEdge = topLeft - bottomLeft;
    glm::vec3 bottomEdge = bottomRight - bottomLeft;
    glm::vec3 diagonal = topRight - bottomLeft;

    glm::vec3 normal1 = _generateNormal(leftEdge, diagonal);
    glm::vec3 normal2 = _generateNormal(bottomEdge, diagonal);

    glm::vec2 texBottomLeft = glm::vec2(0.0f, 0.0f);
    glm::vec2 texBottomRight = glm::vec2(1.0f, 0.0f);
    glm::vec2 texTopLeft = glm::vec2(0.0f, 1.0f);
    glm::vec2 texTopRight = glm::vec2(1.0f, 1.0f);

    vertices.emplace_back(bottomLeft, normal1, texBottomLeft);
    vertices.emplace_back(topLeft, normal1, texTopLeft);
    vertices.emplace_back(topRight, normal1, texTopRight);
    vertices.emplace_back(bottomRight, normal2, texBottomRight);

    for (int i : {0, 1, 2})
    {
        indices.push_back(currentVertices + i);
    }
    for (int i : {2, 3, 0})
    {
        indices.push_back(currentVertices + i);
    }
}

glm::vec3 Generator::_generateVertex(float x, float z, float size)
{
    float y = _noise->generate(x, z, octaves, amplitude, frequency,
                                    amplitudeFactor, frequencyFactor);
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
    model->meshes.push_back(_generateMesh(size, texturePath, textureType));
    model->meshes[0].textures.push_back(texture);
    Logger::log("Terrain generated", info);
}

#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <rendering/Shader.h>
#include <rendering/Texture.h>
#include <string>
#include <vector>

#include <resources/AssetManager.h>

struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
    std::vector<VertexData> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<std::string> _texturePaths;
    AssetManager& _assetManager;
    unsigned int _vao{}, _vbo{}, _ebo{};
public:
    Mesh(const std::vector<VertexData>& vertices, const std::vector<unsigned int>& indices,
         const std::vector<std::string>& texturePaths, AssetManager& assetManager);

    void draw(const Shader& shader);
};
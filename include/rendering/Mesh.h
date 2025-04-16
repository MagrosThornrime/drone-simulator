#pragma once
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <rendering/Shader.h>
#include <rendering/Texture.h>
#include <string>
#include <vector>

struct VertexData {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
    std::vector<VertexData> _vertices;
    std::vector<unsigned int> _indices;
    unsigned int _vao{}, _vbo{}, _ebo{};
public:
    std::vector<std::string> texturePaths;
    std::vector<std::string> textureTypes;
    std::vector<Texture*> textures;

    Mesh(const std::vector<VertexData>& vertices, const std::vector<unsigned int>& indices,
         const std::vector<std::string>& texturePaths, const std::vector<std::string>& textureTypes);

    void draw(const Shader& shader);
};
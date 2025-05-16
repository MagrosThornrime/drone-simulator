#pragma once

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <string>
#include <vector>
#include <Logger.h>
#include <rendering/Mesh.h>
#include <rendering/Shader.h>

class Model
{
    std::string _directory;

    void _processNode(const aiNode& node, const aiScene& scene);

    Mesh _processMesh(aiMesh& mesh, const aiScene& scene);

    void _loadMaterialTextures(const aiMaterial& mat, aiTextureType type, const std::string& typeName,
        std::vector<std::string>& texturePaths, std::vector<std::string>& textureTypes);

    void _normalize();

public:
    std::vector<Mesh> meshes;

    void generate(const std::string& directory, const std::string& objFile);

    void draw(const Shader& shader);

    Model() = default;

};

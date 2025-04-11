#pragma once

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <rendering/Mesh.h>
#include <rendering/Shader.h>
#include <rendering/Texture.h>

#include <string>
#include <vector>

#include <Logger.h>

#include <resources/AssetManager.h>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
    std::vector<Mesh> _meshes;
    std::string _directory;
    AssetManager& _assetManager;

    void _processNode(aiNode *node, const aiScene *scene);

    Mesh _processMesh(aiMesh *mesh, const aiScene *scene);

    void _loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName,
        std::vector<std::string>& texturePaths);
public:

    Model(const std::string& path, AssetManager& assetManager);

    void draw(const Shader& shader);

};
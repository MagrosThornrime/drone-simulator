#include <rendering/Model.h>

#include "resources/AssetManager.h"

Model::Model(const std::string& path, AssetManager& assetManager) : _assetManager(assetManager)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::string text = "Assimp error: " + std::string(importer.GetErrorString());
        Logger::log(text, error);
        throw std::runtime_error(text);
    }

    // process ASSIMP's root node recursively
    _processNode(scene->mRootNode, scene);
}

void Model::draw(const Shader& shader)
{
    for(unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i].draw(shader);
}

void Model::_processNode(aiNode *node, const aiScene *scene)
{
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(_processMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        _processNode(node->mChildren[i], scene);
    }
}

Mesh Model::_processMesh(aiMesh *mesh, const aiScene *scene)
    {
        // data to fill
        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;
        std::vector<std::string> texturePaths;

        // walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            VertexData vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }
            // texture coordinates
            if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = vec;
            }
            else
                vertex.texCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        _loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", texturePaths);
        // 2. specular maps
        _loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", texturePaths);
        // 3. normal maps
        _loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", texturePaths);
        // 4. height maps
        _loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", texturePaths);

        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, indices, texturePaths, _assetManager);
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    void Model::_loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName,
        std::vector<std::string>& texturePaths)
    {
        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            std::string path = "assets/models/tree/" + std::string(str.C_Str());  //TODO: use std::filesystem
            if(!_assetManager.hasTexture(path))
            {
                TextureParameters texParameters;
                _assetManager.loadTexture(path, true, typeName, texParameters, path);
                texturePaths.push_back(path);
            }
        }
}

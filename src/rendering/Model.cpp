#include <rendering/Model.h>
#include <assimp/postprocess.h>


void Model::generate(const std::string& directory, const std::string& objFile)
{
    _directory = directory;
    std::string path = directory + "/" + objFile;
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
    _processNode(*scene->mRootNode, *scene);

    _normalize();
}

void Model::draw(const Shader& shader)
{
    for(int i = 0; i < meshes.size(); i++)
        meshes[i].draw(shader);
}

void Model::_processNode(const aiNode& node, const aiScene& scene)
{
    // process each mesh located at the current node
    for(int i = 0; i < node.mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh& mesh = *scene.mMeshes[node.mMeshes[i]];
        meshes.push_back(_processMesh(mesh, scene));
    }
    // after we've processed all the meshes (if any) we then recursively process each of the children nodes
    for(int i = 0; i < node.mNumChildren; i++)
    {
        _processNode(*node.mChildren[i], scene);
    }
}

Mesh Model::_processMesh(aiMesh& mesh, const aiScene& scene)
    {
        // data to fill
        std::vector<VertexData> vertices;
        std::vector<unsigned int> indices;
        std::vector<std::string> texturePaths;
        std::vector<std::string> textureTypes;

        // walk through each of the mesh's vertices
        for(int i = 0; i < mesh.mNumVertices; i++)
        {
            VertexData vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh.mVertices[i].x;
            vector.y = mesh.mVertices[i].y;
            vector.z = mesh.mVertices[i].z;
            vertex.position = vector;
            // normals
            if (mesh.HasNormals())
            {
                vector.x = mesh.mNormals[i].x;
                vector.y = mesh.mNormals[i].y;
                vector.z = mesh.mNormals[i].z;
                vertex.normal = vector;
            }
            // texture coordinates
            if(mesh.mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh.mTextureCoords[0][i].x;
                vec.y = mesh.mTextureCoords[0][i].y;
                vertex.texCoords = vec;
            }
            else
                vertex.texCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(int i = 0; i < mesh.mNumFaces; i++)
        {
            aiFace face = mesh.mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene.mMaterials[mesh.mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        _loadMaterialTextures(*material, aiTextureType_DIFFUSE, "texture_diffuse",
            texturePaths, textureTypes);
        // 2. specular maps
        _loadMaterialTextures(*material, aiTextureType_SPECULAR, "texture_specular",
            texturePaths, textureTypes);
        // 3. normal maps
        _loadMaterialTextures(*material, aiTextureType_HEIGHT, "texture_normal",
            texturePaths, textureTypes);
        // 4. height maps
        _loadMaterialTextures(*material, aiTextureType_AMBIENT, "texture_height",
            texturePaths, textureTypes);

        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, indices, texturePaths, textureTypes);
    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    void Model::_loadMaterialTextures(const aiMaterial& mat, aiTextureType type, const std::string& typeName,
        std::vector<std::string>& texturePaths, std::vector<std::string>& textureTypes)
    {
        for(int i = 0; i < mat.GetTextureCount(type); i++)
        {
            aiString str;
            mat.GetTexture(type, i, &str);
            std::string path = _directory + "/" + str.C_Str();
            texturePaths.push_back(path);
            textureTypes.push_back(typeName);
        }
}

void Model::_normalize()
{
    Boundaries bounds;
    for (auto& mesh : meshes)
    {
        mesh.findBoundaries(bounds);
    }
    for (auto& mesh : meshes)
    {
        mesh.normalize(bounds);
    }
}

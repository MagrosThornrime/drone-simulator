#pragma once
#include <rendering/Model.h>
#include <unordered_map>
#include <rendering/Texture.h>
#include <rendering/Shader.h>
#include <Logger.h>


class AssetManager{
    std::unordered_map<std::string, Texture> _textures;
    std::unordered_map<std::string, Shader> _shaders;
    std::unordered_map<std::string, Model> _models;
    std::string _configFile;

    void _loadProgramCode(const std::string& path, std::string& code);
    Image _loadImage(const std::string &path, bool flipped);

public:
    float windowWidth{}, windowHeight{};
    std::string windowTitle;

    explicit AssetManager(const std::string& configFile);
    AssetManager(const AssetManager&) = delete;

    Shader* loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                       const std::string& name);
    Shader* loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                           const std::string& geometryPath, const std::string& name);
    Shader* getShader(const std::string& name);
    bool hasShader(const std::string& name);

    void loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                            TextureParameters textureParameters, const std::string& name);
    void loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                            const std::string& name);

    Texture* getTexture(const std::string& name);
    bool hasTexture(const std::string& name);

    void loadModel(const std::string& directory, const std::string& objFile, const std::string& name);
    Model* createEmptyModel(const std::string& name);
    Model* getModel(const std::string& name);
    bool hasModel(const std::string& name);

    void loadGameAssets();
    void loadWindowData();

    ~AssetManager();

};

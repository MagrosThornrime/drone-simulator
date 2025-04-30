#pragma once
#include <rendering/Model.h>
#include <unordered_map>
#include <rendering/Texture.h>
#include <rendering/Shader.h>
#include <Logger.h>


class AssetManager{
    inline static std::unordered_map<std::string, Texture> _textures;
    inline static std::unordered_map<std::string, Shader> _shaders;
    inline static std::unordered_map<std::string, Model> _models;
    inline static std::string _configFile;

    static void _loadProgramCode(const std::string& path, std::string& code);
    static Image _loadImage(const std::string &path, bool flipped);

public:
    inline static float windowWidth, windowHeight;
    inline static std::string windowTitle;

    static void initialize(const std::string& configFile);

    static Shader* loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                       const std::string& name);
    static Shader* loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                           const std::string& geometryPath, const std::string& name);
    static Shader* getShader(const std::string& name);
    static bool hasShader(const std::string& name);

    static void loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                            TextureParameters textureParameters, const std::string& name);
    static void loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                            const std::string& name);

    static Texture* getTexture(const std::string& name);
    static bool hasTexture(const std::string& name);

    static void loadModel(const std::string& directory, const std::string& objFile, const std::string& name);
    static Model* createEmptyModel(const std::string& name);
    static Model* getModel(const std::string& name);
    static bool hasModel(const std::string& name);

    static void loadGameAssets();
    static void loadWindowData();

    static void destroy();

};

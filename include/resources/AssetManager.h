#pragma once

#include <unordered_map>

#include <rendering/Texture.h>
#include <rendering/Shader.h>
#include <Logger.h>


class AssetManager{
    std::unordered_map<std::string, Texture> _textures;
    std::unordered_map<std::string, Shader> _shaderPrograms;
    std::string _configFile;
    float _windowWidth, _windowHeight;
    std::string _windowTitle;

    void _loadProgramCode(const std::string& path, std::string& code);
    Image _loadImage(const std::string &path, ImageType imageType, bool flipped);

public:

    AssetManager(const std::string& configFile);

    Shader* loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                           const std::string& name);
    Shader* loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                           const std::string& geometryPath, const std::string& name);
    Shader* getShader(const std::string& name);

    void loadTexture(const std::string& path, ImageType imageType, bool flipped,
                     TextureParameters textureParameters, const std::string& name);
    Texture* getTexture(const std::string& name);

    void loadGameAssets();

    void loadWindowData();

    float getWindowWidth() { return _windowWidth; }
    float getWindowHeight() { return _windowHeight; }
    std::string getWindowTitle() { return _windowTitle; }

    ~AssetManager();

};
#include <iostream>
#include <ranges>
#include <resources/AssetManager.h>
#include <resources/FileIO.h>


void AssetManager::_loadProgramCode(const std::string& path, std::string& code){
    loadTextFile(path, code);
}

Shader* AssetManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                                        const std::string& name) {
    std::string vertexCode, fragmentCode;
    _loadProgramCode(vertexPath, vertexCode);
    _loadProgramCode(fragmentPath, fragmentCode);
    _shaders.try_emplace(name, vertexCode, fragmentCode);
    _shaders[name].compileProgram();
    Logger::log("Shader loaded: " + name, info);
    return getShader(name);
}

Shader* AssetManager::loadShader(const std::string &vertexPath, const std::string &fragmentPath,
                                        const std::string &geometryPath, const std::string &name) {
    std::string vertexCode, fragmentCode, geometryCode;
    _loadProgramCode(vertexPath, vertexCode);
    _loadProgramCode(fragmentPath, fragmentCode);
    _loadProgramCode(geometryPath, geometryCode);
    _shaders.try_emplace(name, vertexCode, fragmentCode, geometryCode);
    _shaders[name].compileProgram();
    Logger::log("Shader loaded: " + name, info);
    return getShader(name);
}

Shader* AssetManager::getShader(const std::string &name) {
    return &(_shaders[name]);
}

bool AssetManager::hasShader(const std::string& name)
{
    return _shaders.contains(name);
}


Image AssetManager::_loadImage(const std::string &path, bool flipped) {
    int width, height;
    unsigned char* data;
    GLenum format;
    loadImage(path, flipped, &width, &height, data, format);
    return {static_cast<unsigned int>(width), static_cast<unsigned int>(height), format, data};
}


void AssetManager::loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                                  TextureParameters textureParameters, const std::string& name) {
    Image image = _loadImage(path, flipped);
    _textures.try_emplace(name);
    _textures[name].generate(image, textureParameters, typeName);
}

void AssetManager::loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                                const std::string& name) {
    TextureParameters textureParameters;
    loadTexture(path, flipped, typeName, textureParameters, name);
    Logger::log("Texture loaded: " + name, info);
}

Texture* AssetManager::getTexture(const std::string &name) {
    if (!hasTexture(name))
    {
        throw std::runtime_error("Texture: " + name + " does not exist");
    }
    return &(_textures[name]);
}

bool AssetManager::hasTexture(const std::string& name) const
{
    return _textures.contains(name);
}

void AssetManager::loadModel(const std::string& directory, const std::string& objFile,
                            const std::string& name)
{
    _models.try_emplace(name);
    _models[name].generate(directory, objFile);
    for (auto& mesh : _models[name].meshes)
    {
        for (int i = 0; i < mesh.texturePaths.size(); i++)
        {
            std::string texturePath = mesh.texturePaths[i];
            std::string textureType = mesh.textureTypes[i];
            if (!hasTexture(texturePath))
            {
                loadTexture(texturePath, true, textureType, texturePath);
                mesh.textures.push_back(getTexture(texturePath));
            }
        }
    }
    Logger::log("Model loaded: " + directory + "/" + objFile, info);
}

Model* AssetManager::createEmptyModel(const std::string& name)
{
    if (_models.contains(name))
    {
        throw std::runtime_error("Model: " + name + " already exists");
    }
    _models.try_emplace(name);
    return getModel(name);
}

Model* AssetManager::getModel(const std::string& name)
{
    if (!_models.contains(name))
    {
        throw std::runtime_error("Model: " + name + " does not exist");
    }
    return &(_models[name]);
}

void AssetManager::close()
{
    for(auto& program : _shaders | std::views::values){
        glDeleteProgram(program.ID);
    }
    for(auto& texture : _textures | std::views::values){
        glDeleteTextures(1, &texture.ID);
    }
    Logger::log("Asset manager closed", info);
}

AssetManager::AssetManager(const std::string& configFile, const std::string& resourcesFile)
    : _configFile(configFile), _resourcesFile(resourcesFile) {
    Logger::log("Asset manager created", info);
}

bool AssetManager::hasModel(const std::string& name) const
{
    return _models.contains(name);
}

void AssetManager::loadGameAssets()
{
    Json::Value resources;
    loadJsonFile(_resourcesFile, resources);

    Json::Value shaders = resources["shader"];
    std::string vertexFile = shaders["vertex"].asString();
    std::string fragmentFile = shaders["fragment"].asString();
    loadShader(vertexFile, fragmentFile, "shader");

    Json::Value models = resources["models"];
    for (auto& model : models)
    {
        std::string name = model["name"].asString();
        std::string directory = model["directory"].asString();
        std::string objFile = model["obj"].asString();
        loadModel(directory, objFile, name);
    }

    Logger::log("Game assets loaded", info);
}

void AssetManager::loadConfiguration()
{
    Json::Value config;
    loadJsonFile(_configFile, config);

    Json::Value window = config["window"];
    windowWidth = window["width"].asFloat();
    windowHeight = window["height"].asFloat();
    windowTitle = window["title"].asString();

    Json::Value renderer = config["renderer"];
    rendererRangeMin = renderer["range-min"].asFloat();
    rendererRangeMax = renderer["range-max"].asFloat();

    Json::Value generator = config["generator"];
    generatorAmplitude = generator["amplitude"].asFloat();
    generatorFrequency = generator["frequency"].asFloat();
    generatorOctaves = generator["octaves"].asInt();
    generatorAmplitudeFactor = generator["amplitude-factor"].asFloat();
    generatorFrequencyFactor = generator["frequency-factor"].asFloat();
    generatorMinY = generator["min-y"].asFloat();
    generatorMaxY = generator["max-y"].asFloat();
    generatorChunkHeight = generator["chunk-height"].asFloat();

    Json::Value terrain = config["terrain"];
    terrainScale = terrain["scale"].asFloat();
    terrainSize = terrain["size"].asInt();

    Json::Value player = config["player"];
    playerMouseSensitivity = player["mouse-sensitivity"].asFloat();
    playerVelocity = player["velocity"].asFloat();
    playerZoom = player["zoom"].asFloat();
}

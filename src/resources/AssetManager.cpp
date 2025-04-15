#include <ranges>
#include <resources/AssetManager.h>
#include <resources/FileIO.h>


void AssetManager::_loadProgramCode(const std::string& path, std::string& code){
    FileIO::loadTextFile(path, code);
}

Shader* AssetManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                                        const std::string& name) {
    std::string vertexCode, fragmentCode;
    _loadProgramCode(vertexPath, vertexCode);
    _loadProgramCode(fragmentPath, fragmentCode);
    _shaders.try_emplace(name, vertexCode, fragmentCode);
    _shaders[name].compileProgram();
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
    return getShader(name);
}

Shader* AssetManager::getShader(const std::string &name) {
    return &(_shaders[name]);
}

Image AssetManager::_loadImage(const std::string &path, bool flipped) {
    int width, height;
    unsigned char* data;
    GLenum format;
    FileIO::loadImage(path, flipped, &width, &height, data, format);
    return {static_cast<unsigned int>(width), static_cast<unsigned int>(height), format, data};
}


void AssetManager::loadTexture(const std::string& path, bool flipped, const std::string& typeName,
                                  TextureParameters textureParameters, const std::string& name) {
    Image image = _loadImage(path, flipped);
    _textures.try_emplace(name);
    _textures[name].generate(image, textureParameters, typeName);
}

Texture* AssetManager::getTexture(const std::string &name) {
    return &(_textures[name]);
}

bool AssetManager::hasTexture(const std::string& name)
{
    return _textures.contains(name);
}


AssetManager::~AssetManager()
{
    for(const auto& program : _shaders | std::views::values){
        glDeleteProgram(program.ID);
    }
    for(auto& texture : _textures | std::views::values){
        glDeleteTextures(1, &texture.ID);
    }
    Logger::log("Asset manager closed", info);
}

AssetManager::AssetManager(const std::string& configFile) : _configFile(configFile) {
    Logger::log("Asset manager created", info);
}

void AssetManager::loadGameAssets()
{
    Json::Value config;
    FileIO::loadJsonFile(_configFile, config);

    Json::Value window = config["window"];
    _windowWidth = window["width"].asFloat();
    _windowHeight = window["height"].asFloat();
    _windowTitle = window["name"].asString();

    Json::Value shaders = config["shader"];
    std::string vertexFile = shaders["vertex"].asString();
    std::string fragmentFile = shaders["fragment"].asString();
    loadShader(vertexFile, fragmentFile, "shader");

    Logger::log("Game assets loaded", info);
}

void AssetManager::loadWindowData()
{
    Json::Value config;
    FileIO::loadJsonFile(_configFile, config);

    Json::Value window = config["window"];
    _windowWidth = window["width"].asFloat();
    _windowHeight = window["height"].asFloat();
    _windowTitle = window["title"].asString();
}

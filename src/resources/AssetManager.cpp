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
    _shaderPrograms.try_emplace(name, vertexCode, fragmentCode);
    _shaderPrograms[name].compileProgram();
    return getShader(name);
}

Shader* AssetManager::loadShader(const std::string &vertexPath, const std::string &fragmentPath,
                                        const std::string &geometryPath, const std::string &name) {
    std::string vertexCode, fragmentCode, geometryCode;
    _loadProgramCode(vertexPath, vertexCode);
    _loadProgramCode(fragmentPath, fragmentCode);
    _loadProgramCode(geometryPath, geometryCode);
    _shaderPrograms.try_emplace(name, vertexCode, fragmentCode, geometryCode);
    _shaderPrograms[name].compileProgram();
    return getShader(name);
}

Shader* AssetManager::getShader(const std::string &name) {
    return &(_shaderPrograms[name]);
}

Image AssetManager::_loadImage(const std::string &path, ImageType imageType, bool flipped) {
    int width, height;
    unsigned char* data;
    FileIO::loadImage(path, flipped, &width, &height, data);
    return {static_cast<unsigned int>(width), static_cast<unsigned int>(height), imageType, data};
}


void AssetManager::loadTexture(const std::string& path, ImageType imageType, bool flipped,
                                  TextureParameters textureParameters, const std::string& name) {
    Image image = _loadImage(path, imageType, flipped);
    _textures[name] = Texture();
    _textures[name].generate(image, textureParameters);
}

Texture* AssetManager::getTexture(const std::string &name) {
    return &(_textures[name]);
}

AssetManager::~AssetManager()
{
    for(const auto& program : _shaderPrograms | std::views::values){
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
    _windowWidth = window["width"].asInt();
    _windowHeight = window["height"].asInt();
    _windowTitle = window["name"].asString();

    Json::Value shaders = config["shader"];
    std::string vertexFile = shaders["vertex"].asString();
    std::string fragmentFile = shaders["fragment"].asString();
    loadShader(vertexFile, fragmentFile, "shader");

    Json::Value textures = config["textures"];
    for (auto& texture : textures)
    {
        TextureParameters textureParameters;
        std::string name = texture["name"].asString();
        std::string path = texture["path"].asString();
        ImageType type = Image::typeFromString(texture["type"].asString());
        bool flipped = texture["flipped"].asBool();
        loadTexture(path, type, flipped, textureParameters, name);
    }
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

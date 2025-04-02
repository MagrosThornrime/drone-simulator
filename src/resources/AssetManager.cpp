#include <resources/AssetManager.h>


void AssetManager::_loadProgramCode(const std::string& path, std::string& code){
    FileIO::loadTextFile(path, code);
}

void AssetManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                                        const std::string& name) {
    std::string vertexCode, fragmentCode;
    _loadProgramCode(vertexPath, vertexCode);
    _loadProgramCode(fragmentPath, fragmentCode);
    _shaderPrograms[name] = Shader(vertexCode, fragmentCode);
    _shaderPrograms[name].compileProgram();
}

void AssetManager::loadShader(const std::string &vertexPath, const std::string &fragmentPath,
                                        const std::string &geometryPath, const std::string &name) {
    std::string vertexCode, fragmentCode, geometryCode;
    _loadProgramCode(vertexPath, vertexCode);
    _loadProgramCode(fragmentPath, fragmentCode);
    _loadProgramCode(geometryPath, geometryCode);
    _shaderPrograms[name] = Shader(vertexCode, fragmentCode, geometryCode);
    _shaderPrograms[name].compileProgram();
}

Shader* AssetManager::getShader(const std::string &name) {
    return &(_shaderPrograms[name]);
}

Image AssetManager::_loadImage(const std::string &path, ImageType imageType,
                                 bool bFlipped) {
    int width, height;
    unsigned char* data;
    FileIO::loadImage(path, bFlipped, &width, &height, data);
    return {(unsigned int)width, (unsigned int)height, imageType, data};

}


void AssetManager::loadTexture(const std::string& path, ImageType imageType, bool bFlipped,
                                  TextureParameters textureParameters, const std::string& name) {
    Image image = _loadImage(path, imageType, bFlipped);
    _textures[name] = Texture();
    _textures[name].generate(image, textureParameters);
}

Texture* AssetManager::getTexture(const std::string &name) {
    return &(_textures[name]);
}

AssetManager::~AssetManager() {
    for(auto [name, program] : _shaderPrograms){
        glDeleteProgram(program.ID);
    }
    for(auto [name, texture] : _textures){
        glDeleteTextures(1, &texture.ID);
    }
    Logger::log("Asset manager closed", info);
}

AssetManager::AssetManager() {
    Logger::log("Asset manager created", info);
}
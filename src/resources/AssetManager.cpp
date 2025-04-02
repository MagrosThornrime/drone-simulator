#include <resources/AssetManager.h>


void AssetManager::loadProgramCode(const std::string& path, std::string& code){
    FileIO::loadTextFile(path, code);
}

void AssetManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath,
                                        const std::string& name) {
    std::string vertexCode, fragmentCode;
    loadProgramCode(vertexPath, vertexCode);
    loadProgramCode(fragmentPath, fragmentCode);
    shaderPrograms[name] = Shader(vertexCode, fragmentCode);
    shaderPrograms[name].compileProgram();
}

void AssetManager::loadShader(const std::string &vertexPath, const std::string &fragmentPath,
                                        const std::string &geometryPath, const std::string &name) {
    std::string vertexCode, fragmentCode, geometryCode;
    loadProgramCode(vertexPath, vertexCode);
    loadProgramCode(fragmentPath, fragmentCode);
    loadProgramCode(geometryPath, geometryCode);
    shaderPrograms[name] = Shader(vertexCode, fragmentCode, geometryCode);
    shaderPrograms[name].compileProgram();
}

Shader* AssetManager::getShader(const std::string &name) {
    return &(shaderPrograms[name]);
}

Image AssetManager::loadImage(const std::string &path, ImageType imageType,
                                 bool bFlipped) {
    int width, height;
    unsigned char* data;
    FileIO::loadImage(path, bFlipped, &width, &height, data);
    return {(unsigned int)width, (unsigned int)height, imageType, data};

}


void AssetManager::loadTexture(const std::string& path, ImageType imageType, bool bFlipped,
                                  TextureParameters textureParameters, const std::string& name) {
    Image image = loadImage(path, imageType, bFlipped);
    textures[name] = Texture();
    textures[name].generate(image, textureParameters);
}

Texture* AssetManager::getTexture(const std::string &name) {
    return &(textures[name]);
}

AssetManager::~AssetManager() {
    for(auto [name, program] : shaderPrograms){
        glDeleteProgram(program.ID);
    }
    for(auto [name, texture] : textures){
        glDeleteTextures(1, &texture.ID);
    }
    Logger::log("Asset manager closed", info);
}

AssetManager::AssetManager() {
    Logger::log("Asset manager created", info);
}
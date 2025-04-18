#define STB_IMAGE_IMPLEMENTATION
#include <resources/FileIO.h>
#include <fstream>
#include <Logger.h>
#include <stb_image.h>


void FileIO::loadTextFile(const std::string &path, std::string &text) {
    std::ifstream file;
    std::stringstream stringStream;

    try {
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file.open(path.c_str());
        stringStream << file.rdbuf();
        file.close();
        text = stringStream.str();
    }
    catch(std::ifstream::failure& e) {
        std::string errorText = e.what();
        Logger::log(errorText, LogLevel::error);
        throw std::runtime_error(errorText);
    }
}

void FileIO::loadImage(const std::string &path, bool flipped, int* width,
                       int* height, unsigned char*& data, GLenum& format)  {
    int nrChannels;

    stbi_set_flip_vertically_on_load(flipped);

    data = stbi_load(path.c_str(), width, height, &nrChannels, 0);

    if(!data)
    {
        const std::string text = "Failed to load image: " + path;
        Logger::log(text, error);
        throw std::runtime_error(text);
    }

    if (nrChannels == 1)
    {
        format = GL_RED;
    }
    else if (nrChannels == 3)
    {
        format = GL_RGB;
    }
    else if (nrChannels == 4)
    {
        format = GL_RGBA;
    }
    else
    {
        throw std::runtime_error("Unsupported number of channels");
    }
}

void FileIO::loadJsonFile(const std::string &path, Json::Value& root) {
    std::string text;
    loadTextFile(path, text);
    std::stringstream textStream(text);
    textStream >> root;
}
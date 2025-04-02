#define STB_IMAGE_IMPLEMENTATION
#include <resources/FileIO.h>
#include <fstream>
#include <Logger.h>
#include <stb_image.h>


void FileIO::loadTextFile(const std::string &path, std::string &text) {
    std::ifstream file;
    std::stringstream stringStream;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path.c_str());
        stringStream << file.rdbuf();
        file.close();
        text = stringStream.str();
    }
    catch(std::ifstream::failure& e) {
        Logger::log("file not successfully read: " + path, LogLevel::error);
    }
}

void FileIO::loadImage(const std::string &path, bool flipped, int* width,
                       int* height, unsigned char*& data)  {
    int nrChannels;

    stbi_set_flip_vertically_on_load(flipped);

    data = stbi_load(path.c_str(), width, height, &nrChannels, 0);

    if(!data)
    {
        const std::string text = "Failed to load image: " + path;
        Logger::log(text, error);
    }
}
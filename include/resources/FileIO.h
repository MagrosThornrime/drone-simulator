#pragma once
#include <sstream>
#include <glad/glad.h>
#include <json/json.h>


struct FileIO{
    static void loadTextFile(const std::string& path, std::string& text);

    static void loadImage(const std::string &path, bool flipped, int* width,
                   int* height, unsigned char*& data, GLenum& format);

    static void loadJsonFile(const std::string& path, Json::Value& root);

};
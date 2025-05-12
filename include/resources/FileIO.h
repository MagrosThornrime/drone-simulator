#pragma once
#include <glad/glad.h>
#include <json/json.h>

void loadTextFile(const std::string& path, std::string& text);
void loadImage(const std::string &path, bool flipped, int* width,
                   int* height, unsigned char*& data, GLenum& format);
void loadJsonFile(const std::string& path, Json::Value& root);

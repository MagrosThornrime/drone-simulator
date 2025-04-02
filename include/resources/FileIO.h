#pragma once
#include <sstream>


struct FileIO{
    static void loadTextFile(const std::string& path, std::string& text);

    static void loadImage(const std::string &path, bool flipped, int* width,
                   int* height, unsigned char*& data);

};
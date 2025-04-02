#pragma once
#include <sstream>


class FileIO{

public:
    static void loadTextFile(const std::string& path, std::string& text);

    static void loadImage(const std::string &path, bool bFlipped, int* width,
                   int* height, unsigned char*& data);

};
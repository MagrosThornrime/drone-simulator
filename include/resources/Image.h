#pragma once
#include <string>
#include <glad\glad.h>

enum ImageType{JPG, PNG};

struct Image{
    unsigned int width{}, height{};
    ImageType imageType{};
    unsigned char* data{};

    Image(unsigned int width, unsigned int height, ImageType imageType, unsigned char* data)
    : width(width), height(height), imageType(imageType), data(data) {}

    ~Image();

    GLint getFormat() const;

    static ImageType typeFromString(const std::string& type);
};
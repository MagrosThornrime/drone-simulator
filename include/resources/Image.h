#pragma once
#include <glad\glad.h>

enum ImageType{eJPG, ePNG};

struct Image{
    unsigned int width{}, height{};
    ImageType imageType{};
    unsigned char* data{};

    Image(unsigned int width, unsigned int height, ImageType imageType, unsigned char* data)
    : width(width), height(height), imageType(imageType), data(data) {}

    ~Image();

    GLint getFormat() const;
};
#pragma once
#include <string>
#include <glad\glad.h>

struct Image{
    unsigned int width{}, height{};
    GLenum format{};
    unsigned char* data{};

    Image(unsigned int width, unsigned int height, GLenum format, unsigned char* data)
    : width(width), height(height), format(format), data(data) {}

    ~Image();

    GLint getFormat() const;

};
#pragma once
#include <glad/glad.h>
#include <stb_image.h>


struct Image{
    unsigned int width{}, height{};
    GLenum format{};
    unsigned char* data{};

    Image(unsigned int width, unsigned int height, GLenum format, unsigned char* data)
    : width(width), height(height), format(format), data(data) {}
    Image(const Image& other)
    : width(other.width), height(other.height), format(other.format), data(other.data) {}
    ~Image() { stbi_image_free(data); }

};
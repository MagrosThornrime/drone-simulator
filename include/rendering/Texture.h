#pragma once
#include <glad\glad.h>
#include <resources/Image.h>

struct TextureParameters{
    GLint wrapS = GL_REPEAT;
    GLint wrapT = GL_REPEAT;
    GLint filterMin = GL_LINEAR_MIPMAP_NEAREST;
    GLint filterMag = GL_LINEAR;
};

struct Texture{
    unsigned int ID{};
    std::string typeName{};

    explicit Texture();
    void generate(const Image& image, TextureParameters textureParameters, const std::string& typeName);
    void bind() const;
    void unbind() const;
};
#pragma once
#include <glad\glad.h>
#include <resources/Image.h>
#include <Logger.h>

struct TextureParameters{
    GLint wrapS = GL_REPEAT;
    GLint wrapT = GL_REPEAT;
    GLint filterMin = GL_LINEAR_MIPMAP_NEAREST;
    GLint filterMag = GL_LINEAR;
};

class Texture{
public:
    unsigned int ID{};

    explicit Texture();
    void generate(const Image& image, TextureParameters textureParameters);
    void bind() const;
    void unbind() const;
};
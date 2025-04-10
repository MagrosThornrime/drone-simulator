#include <rendering/Texture.h>
#include <Logger.h>

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::generate(const Image& image, TextureParameters textureParameters) {
    bind();
    if(image.data)
    {
        const GLint internalFormat = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.width,
                     image.height, 0, image.getFormat(), GL_UNSIGNED_BYTE, image.data);
    }
    else{
        std::string text = "Failed to load texture";
        Logger::log(text, error);
        throw std::runtime_error(text);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureParameters.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureParameters.wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureParameters.filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureParameters.filterMag);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
}


Texture::Texture() {
    glGenTextures(1, &ID);
}
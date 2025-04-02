#include <resources/Image.h>
#include <stb_image.h>

Image::~Image(){
    stbi_image_free(data);
}

GLint Image::getFormat() const {
    GLint format;
    switch(imageType){
    case ImageType::eJPG:
        format = GL_RGB;
        break;
    case ImageType::ePNG:
        format = GL_RGBA;
        break;
    }
    return format;
}
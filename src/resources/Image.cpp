#include <resources/Image.h>
#include <stb_image.h>
#include <stdexcept>
#include <string>

Image::~Image(){
    stbi_image_free(data);
}

GLint Image::getFormat() const {
    switch(imageType){
        case JPG:
            return GL_RGB;
        case PNG:
            return GL_RGBA;
        default:
            throw std::runtime_error("Unknown image type");
    }
}

ImageType Image::typeFromString(const std::string& type)
{
    if (type == "JPG")
    {
        return JPG;
    }
    if (type == "PNG")
    {
        return PNG;
    }
    throw std::runtime_error("Unknown image type: " + type);
}
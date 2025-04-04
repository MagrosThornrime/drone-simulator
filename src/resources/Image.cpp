#include <resources/Image.h>
#include <stb_image.h>

Image::~Image(){
    stbi_image_free(data);
}

GLint Image::getFormat() const {
    switch(imageType){
        case JPG:
            return GL_RGB;
        case PNG:
            return GL_RGBA;
    }
}
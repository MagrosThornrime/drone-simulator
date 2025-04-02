#include <resources/Image.h>
#include <stb_image.h>

Image::~Image(){
    stbi_image_free(data);
}

GLint Image::getFormat() const {
    switch(imageType){
        case eJPG:
            return GL_RGB;
        case ePNG:
            return GL_RGBA;
    }
}
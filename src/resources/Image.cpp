#include <resources/Image.h>
#include <stb_image.h>
#include <stdexcept>
#include <string>

Image::~Image(){
    stbi_image_free(data);
}

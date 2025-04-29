#include <resources/Image.h>
#include <stb_image.h>

Image::~Image(){
    stbi_image_free(data);
}

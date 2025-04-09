#pragma once
#include "Shader.h"
#include <rendering/Texture.h>

class Renderer{

    Shader* _shader;
    unsigned int _vao{}, _vbo{};

    void _initData();


public:
    Renderer(Shader* shader);
    ~Renderer();
    void drawBackground();
    void drawSprite(Texture* texture);
};

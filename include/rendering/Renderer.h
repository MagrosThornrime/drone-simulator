#pragma once
#include "Shader.h"

class Renderer{

    Shader* _shader;
    unsigned int _vao{}, _vbo{};

    void _initData();


public:
    Renderer(Shader* shader);
    ~Renderer();
    void drawBackground();
    void drawSprite();
};

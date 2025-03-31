#pragma once

class Renderer{

    float _vertices[9] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int _vbo{};

public:
    Renderer();

    void draw();
};
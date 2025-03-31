#include <Renderer.h>
#include <glad/glad.h>

void Renderer::draw(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
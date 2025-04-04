#include <Application.h>
#include <rendering/Renderer.h>

#include "resources/AssetManager.h"


const std::string vertexFile = "shaders/vertex.glsl";
const std::string fragmentFile = "shaders/fragment.glsl";
const std::string shaderName = "shader";

int main()
{
    Application application;
    AssetManager assetManager;
    Shader* shader = assetManager.loadShader(vertexFile, fragmentFile, shaderName);
    Renderer renderer(shader);

    while (application.isActive())
    {
        application.getKeys();
        if (application.isKeyPressed(GLFW_KEY_ESCAPE))
        {
            application.close();
        }
        renderer.drawBackground();
        renderer.drawSprite();
        application.update();
    }

    return 0;
}

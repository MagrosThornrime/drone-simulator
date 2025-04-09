#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>



const std::string shaderName = "shader";

int main()
{
    Application application;
    AssetManager assetManager("config.json");
    assetManager.loadGameAssets("shader");
    Renderer renderer(assetManager.getShader(shaderName));

    while (application.isActive())
    {
        application.getKeys();
        if (application.isKeyPressed(GLFW_KEY_ESCAPE))
        {
            application.close();
        }
        renderer.drawBackground();
        renderer.drawSprite(assetManager.getTexture("wall"));
        application.update();
    }

    return 0;
}

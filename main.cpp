#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>



int main()
{
    AssetManager::initialize("config.json");
    AssetManager::loadWindowData();
    Application::initialize(AssetManager::windowWidth, AssetManager::windowHeight,
        AssetManager::windowTitle);
    AssetManager::loadGameAssets();

    Renderer::initialize(AssetManager::getShader("shader"));

    while (Application::isActive())
    {
        Application::getKeys();
        if (Application::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            Application::close();
        }
        Renderer::drawBackground();
        // Model* model = AssetManager::getModel("drone");
        // Renderer::drawModel(model, {0,0,0}, {0.01, 0.01, 0.01}, {1, 0, 0}, 0);
        Model* model = AssetManager::getModel("backpack");
        Renderer::drawModel(model, {0,0,0}, {0.5, 0.5, 0.5}, {1, 0, 0}, 0);

        Application::update();
    }

    Renderer::destroy();
    Application::destroy();
    AssetManager::destroy();

    return 0;
}

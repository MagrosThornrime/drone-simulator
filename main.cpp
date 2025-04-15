#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>



int main()
{
    AssetManager assetManager("config.json");
    assetManager.loadWindowData();
    Application::initialize(assetManager.getWindowWidth(), assetManager.getWindowHeight(),
        assetManager.getWindowTitle());
    assetManager.loadGameAssets();

    Model model("assets/models/drone/drone_low_poly.obj", assetManager);

    Renderer renderer(assetManager.getShader("shader"));

    while (Application::isActive())
    {
        Application::getKeys();
        if (Application::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            Application::close();
        }
        renderer.drawBackground();
        renderer.drawModel(&model, {0,0,0}, {0.01, 0.01, 0.01}, {1, 0, 0}, 0);
        Application::update();
    }

    return 0;
}

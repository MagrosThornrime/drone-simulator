#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>



glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main()
{
    AssetManager assetManager("config.json");
    assetManager.loadWindowData();
    Application::initialize(assetManager.getWindowWidth(), assetManager.getWindowHeight(),
        assetManager.getWindowTitle());
    assetManager.loadGameAssets();

    Renderer renderer(assetManager.getShader("shader"));

    while (Application::isActive())
    {
        Application::getKeys();
        if (Application::isKeyPressed(GLFW_KEY_ESCAPE))
        {
            Application::close();
        }
        renderer.drawBackground();
        for (int i=0; i < 10; i++)
        {
            glm::vec3 position = cubePositions[i];
            float angle = 20.0f * i;
            glm::vec3 rotationAxis = {1.0, 0.3f, 0.5f};
            glm::vec3 scale = glm::vec3(1.0f);
            renderer.drawSprite(assetManager.getTexture("wall"), position, scale, rotationAxis, angle);
        }
        Application::update();
    }

    return 0;
}

#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>
#include <Camera.h>

#include <terrain/Generator.h>

void setup()
{
    AssetManager::initialize("config.json");
    AssetManager::loadWindowData();
    Application::initialize(AssetManager::windowWidth, AssetManager::windowHeight,
        AssetManager::windowTitle);
    AssetManager::loadGameAssets();
    Renderer::initialize(AssetManager::getShader("shader"));
    Generator generator(256, 1312421);
    generator.generateTerrain("terrain", 512, 512);
}

void close()
{
    Renderer::destroy();
    AssetManager::destroy();
    Application::destroy();
}

void drawModel()
{
    Model* model = AssetManager::getModel("terrain");
    Renderer::drawModel(model, glm::vec3(0.0f), glm::vec3(0.05f), {1, 0, 0}, 0);
}

void processInput(Camera& camera, float deltaTime)
{
    auto lock = std::lock_guard(Application::mutex);
    Application::getKeys();
    if (Application::isKeyPressed(GLFW_KEY_ESCAPE))
    {
        Application::close();
    }
    if (Application::isKeyPressed(GLFW_KEY_W) || Application::isKeyPressed(GLFW_KEY_UP))
    {
        camera.move(FORWARD, deltaTime);
    }
    if (Application::isKeyPressed(GLFW_KEY_S) || Application::isKeyPressed(GLFW_KEY_DOWN))
    {
        camera.move(BACKWARD, deltaTime);
    }
    if (Application::isKeyPressed(GLFW_KEY_A) || Application::isKeyPressed(GLFW_KEY_LEFT))
    {
        camera.move(LEFT, deltaTime);
    }
    if (Application::isKeyPressed(GLFW_KEY_D) || Application::isKeyPressed(GLFW_KEY_RIGHT))
    {
        camera.move(RIGHT, deltaTime);
    }
    if (Application::isMouseMoved)
    {
        camera.processMouseMovement(Application::xMoveOffset, Application::yMoveOffset);
        Application::isMouseMoved = false;
    }
    if (Application::isMouseScrolled)
    {
        camera.processMouseScroll(Application::scrollOffset);
        Application::isMouseScrolled = false;
    }
}

float getDeltaTime(float& lastTime)
{
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime;
}

int main()
{
    setup();

    Camera camera;
    float lastTime = 0.0f;

    while (Application::isActive())
    {
        float deltaTime = getDeltaTime(lastTime);

        processInput(camera, deltaTime);

        Renderer::setViewMatrix(camera.position, camera.front, camera.up);
        Renderer::zoom = camera.zoom;
        Renderer::drawBackground();

        drawModel();
        Application::update();
    }

    close();

    return 0;
}

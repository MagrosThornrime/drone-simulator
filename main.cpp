#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>
#include <terrain/Generator.h>
#include <Player.h>
#include <GameObject.h>


void processInput(Application& application, Player& player, float deltaTime)
{
    application.getKeys();
    if (application.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        application.close();
    }
    if (application.isKeyPressed(GLFW_KEY_W) || application.isKeyPressed(GLFW_KEY_UP))
    {
        player.move(FORWARD, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_S) || application.isKeyPressed(GLFW_KEY_DOWN))
    {
        player.move(BACKWARD, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_A) || application.isKeyPressed(GLFW_KEY_LEFT))
    {
        player.move(LEFT, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_D) || application.isKeyPressed(GLFW_KEY_RIGHT))
    {
        player.move(RIGHT, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_Q) || application.isKeyPressed(GLFW_KEY_SPACE))
    {
        player.move(UP, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_E) || application.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        player.move(DOWN, deltaTime);
    }
    if (application.isMouseMoved)
    {
        player.processMouseMovement(application.xMoveOffset, application.yMoveOffset);
        application.isMouseMoved = false;
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
    AssetManager assetManager("config.json");
    assetManager.loadConfiguration();
    Application application(assetManager.windowWidth, assetManager.windowHeight,
        assetManager.windowTitle);
    assetManager.loadGameAssets();
    Renderer renderer(assetManager.getShader("shader"), application.windowWidth, application.windowHeight,
        assetManager.renderRangeMin, assetManager.renderRangeMax);
    Generator generator(500, 0.0f, 0.1f);
    generator.generateTerrain(assetManager, "terrain", 500);
    GameObject terrain("terrain", glm::vec3(0.0f), glm::vec3(5000.0f));
    Player drone("drone", {0.0f, 3000.0f, 0.0f}, glm::vec3(1.0f));

    renderer.zoom = drone.getZoom();

    float lastTime = 0.0f;

    while (application.isActive())
    {
        float deltaTime = getDeltaTime(lastTime);

        processInput(application, drone, deltaTime);

        drone.updateViewZone(renderer);
        renderer.drawBackground();

        terrain.draw(renderer, assetManager);
        drone.draw(renderer, assetManager);
        application.update();
    }

    assetManager.close();
    
    return 0;
}

#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>
#include <terrain/Generator.h>
#include <game_objects/Player.h>
#include <collisions/GJK.h>


void processInput(Application& application, Player& player, float deltaTime, const std::vector<GameObject*>& collidables)
{
    application.getKeys();
    if (application.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        application.close();
    }
    if (application.isKeyPressed(GLFW_KEY_W) || application.isKeyPressed(GLFW_KEY_UP))
    {
        player.move(FORWARD, deltaTime, collidables);
    }
    if (application.isKeyPressed(GLFW_KEY_S) || application.isKeyPressed(GLFW_KEY_DOWN))
    {
        player.move(BACKWARD, deltaTime, collidables);
    }
    if (application.isKeyPressed(GLFW_KEY_A) || application.isKeyPressed(GLFW_KEY_LEFT))
    {
        player.move(LEFT, deltaTime, collidables);
    }
    if (application.isKeyPressed(GLFW_KEY_D) || application.isKeyPressed(GLFW_KEY_RIGHT))
    {
        player.move(RIGHT, deltaTime, collidables);
    }
    if (application.isKeyPressed(GLFW_KEY_Q) || application.isKeyPressed(GLFW_KEY_SPACE))
    {
        player.move(UP, deltaTime, collidables);
    }
    if (application.isKeyPressed(GLFW_KEY_E) || application.isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        player.move(DOWN, deltaTime, collidables);
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
    generator.generateTerrain(assetManager, "terrain", 200);
    GameObject terrain("terrain", glm::vec3(0.0f), glm::vec3(1000.0f), assetManager);
    // Player drone("drone", {0.0f, 500.0f, 0.0f}, glm::vec3(0.003f), assetManager, 0.5f);
    Player drone("cube", {0.0f, 700.0f, 0.0f}, glm::vec3(5.0f), assetManager, 50.0f);

    GameObject crate("bred", {100.0f, 500.0f, 0.0f}, glm::vec3(10.0f), assetManager);

    std::vector<GameObject*> collidables = {&crate, &terrain};
    std::vector<GameObject*> drawables = {&terrain, &drone, &crate};

    renderer.zoom = drone.getZoom();

    float lastTime = 0.0f;

    while (application.isActive())
    {
        float deltaTime = getDeltaTime(lastTime);

        processInput(application, drone, deltaTime, collidables);

        drone.updateViewZone(renderer);
        renderer.drawBackground();

        for (GameObject* drawable : drawables)
        {
            drawable->draw(renderer, assetManager);
        }

        application.update();
    }

    assetManager.close();
    
    return 0;
}

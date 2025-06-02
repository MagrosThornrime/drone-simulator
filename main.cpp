#include <Application.h>
#include <iostream>
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
    {
        auto lock = std::lock_guard(application.mouseMutex);
        if (application.isMouseMoved)
        {
            player.processMouseMovement(application.xMoveOffset, application.yMoveOffset);
            application.isMouseMoved = false;
        }
    }
    if (application.isKeyPressed(GLFW_KEY_1))
    {
        player.setCameraMode(THIRD_PERSON);
    }
    if (application.isKeyPressed(GLFW_KEY_2))
    {
        player.setCameraMode(FIRST_PERSON);
    }
    if (application.isKeyPressed(GLFW_KEY_3))
    {
        player.setCameraMode(TOP_DOWN);
    }
}

float getDeltaTime(float& lastTime)
{
    float currentTime = glfwGetTime();
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime;
}

void setGeneratorConfig(Generator& generator, const AssetManager& assetManager)
{
    generator.amplitude = assetManager.generatorAmplitude;
    generator.octaves = assetManager.generatorOctaves;
    generator.frequency = assetManager.generatorFrequency;
    generator.amplitudeFactor = assetManager.generatorAmplitudeFactor;
    generator.frequencyFactor = assetManager.generatorFrequencyFactor;
    generator.minY = assetManager.generatorMinY;
    generator.maxY = assetManager.generatorMaxY;
    generator.chunkHeight = assetManager.generatorChunkHeight;
}

int main()
{
    AssetManager assetManager("config/config.json", "config/resources.json");
    assetManager.loadConfiguration();
    Application application(assetManager.windowWidth, assetManager.windowHeight,
        assetManager.windowTitle);
    assetManager.loadGameAssets();
    Renderer renderer(assetManager.getShader("shader"), application.windowWidth, application.windowHeight,
        assetManager.rendererRangeMin, assetManager.rendererRangeMax);
    Generator generator(500, 0.0f, 0.1f);
    setGeneratorConfig(generator, assetManager);

    generator.generateTerrain(assetManager, "terrain", assetManager.terrainSize);
    GameObject terrain("terrain", glm::vec3(0.0f), glm::vec3(assetManager.terrainScale), assetManager);
    float playerHeight = assetManager.generatorMaxY * assetManager.terrainScale;
    Player drone("drone", {0.0f, playerHeight, 0.0f}, glm::vec3(0.01f), assetManager);

    std::vector collidables = {&terrain};
    std::vector<GameObject*> drawables = {&terrain, &drone};

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

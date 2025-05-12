#include <Application.h>
#include <rendering/Renderer.h>
#include <resources/AssetManager.h>
#include <Camera.h>
#include <terrain/Generator.h>


void drawModel(AssetManager& assetManager, Renderer& renderer)
{
    Model* model = assetManager.getModel("terrain");
    renderer.drawModel(model, glm::vec3(0.0f), glm::vec3(1.0f), {1, 0, 0}, 0);
}

void processInput(Application& application, Camera& camera, float deltaTime)
{
    application.getKeys();
    if (application.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        application.close();
    }
    if (application.isKeyPressed(GLFW_KEY_W) || application.isKeyPressed(GLFW_KEY_UP))
    {
        camera.move(FORWARD, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_S) || application.isKeyPressed(GLFW_KEY_DOWN))
    {
        camera.move(BACKWARD, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_A) || application.isKeyPressed(GLFW_KEY_LEFT))
    {
        camera.move(LEFT, deltaTime);
    }
    if (application.isKeyPressed(GLFW_KEY_D) || application.isKeyPressed(GLFW_KEY_RIGHT))
    {
        camera.move(RIGHT, deltaTime);
    }
    if (application.isMouseMoved)
    {
        camera.processMouseMovement(application.xMoveOffset, application.yMoveOffset);
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
    assetManager.loadWindowData();
    Application application(assetManager.windowWidth, assetManager.windowHeight,
        assetManager.windowTitle);
    assetManager.loadGameAssets();
    Renderer renderer(assetManager.getShader("shader"), application.windowWidth, application.windowHeight);
    Generator generator(500, 0.0f, 0.1f);
    generator.generateTerrain(assetManager, "terrain", 500);

    Camera camera;
    renderer.zoom = camera.zoom;

    float lastTime = 0.0f;

    while (application.isActive())
    {
        float deltaTime = getDeltaTime(lastTime);

        processInput(application, camera, deltaTime);

        renderer.setViewMatrix(camera.position, camera.front, camera.up);
        renderer.drawBackground();

        drawModel(assetManager, renderer);
        application.update();
    }
    
    return 0;
}

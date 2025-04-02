#include <Application.h>
#include <Renderer.h>


int main()
{
    Application application;
    Renderer renderer;

    while (application.isActive())
    {
        application.getKeys();
        if (application.currentKeys.contains(GLFW_KEY_ESCAPE))
        {
            application.close();
        }
        renderer.draw();
        application.update();
    }

    return 0;
}

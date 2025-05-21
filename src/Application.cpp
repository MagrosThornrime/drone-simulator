#include <Application.h>
#include <Logger.h>


void glfwError(int id, const char* description)
{
    std::string text = "GLFW Error: " + std::string(description);
    Logger::log(text, error);
}


void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!application)
    {
        throw std::runtime_error("GLFW callback can't see Application");
    }
    auto lock = std::lock_guard(application->mutex);
    if (application->firstMouseMove)
    {
        application->lastMouseX = xpos;
        application->lastMouseY = ypos;
        application->firstMouseMove = false;
    }

    application->xMoveOffset = xpos - application->lastMouseX;
    application->yMoveOffset = application->lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

    application->lastMouseX = xpos;
    application->lastMouseY = ypos;
    application->isMouseMoved = true;
}


Application::Application(int width, int height, const std::string& windowName)
    : windowWidth(width), windowHeight(height)
{

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Uncomment if you use Mac OS X
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Register error callback funtion
    glfwSetErrorCallback(&glfwError);

    // Create GLFW window
    _window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
    if (_window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Use this window as the main OpenGL context
    glfwMakeContextCurrent(_window);

    // Load the addresses of OpenGL function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::string text = "Failed to initialize GLAD";
        Logger::log(text, error);
        throw std::runtime_error(text);
    }

    // Set size of the rendering window
    glViewport(0, 0, windowWidth, windowHeight);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Pass Application to glfw callbacks
    glfwSetWindowUserPointer(_window, this);

    // Set callbacks for capturing mouse events
    glfwSetCursorPosCallback(_window, mouseMoveCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Without this enabled, you would see through 3D objects
    glEnable(GL_DEPTH_TEST);

    Logger::log("Application started", info);
}

bool Application::isActive()
{
    return !glfwWindowShouldClose(_window);
}

void Application::close()
{
    glfwSetWindowShouldClose(_window, true);
}

void Application::getKeys()
{
    auto lock = std::lock_guard(mutex);
    currentKeys.clear();
    for (auto key : _listenedKeys)
    {
        if(glfwGetKey(_window, key) == GLFW_PRESS)
        {
            currentKeys.insert(key);
        }
    }
}

void Application::update()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}


Application::~Application(){
    glfwTerminate();
    Logger::log("Application closed", info);
}

bool Application::isKeyPressed(int key)
{
    return currentKeys.contains(key);
}
#include <Application.h>
#include <Logger.h>
#include <sstream>


void glfwError(int id, const char* description)
{
    std::string text = "GLFW Error: " + std::string(description);
    Logger::log(text, error);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Application::windowWidth = width;
    Application::windowHeight = height;
    glViewport(0, 0, width, height);
}

void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto lock = std::lock_guard(Application::mutex);
    if (Application::firstMouseMove)
    {
        Application::lastMouseX = xpos;
        Application::lastMouseY = ypos;
        Application::firstMouseMove = false;
    }

    Application::xMoveOffset = xpos - Application::lastMouseX;
    Application::yMoveOffset = Application::lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

    Application::lastMouseX = xpos;
    Application::lastMouseY = ypos;
    Application::isMouseMoved = true;
}


void Application::initialize(int width, int height, const std::string& windowName)
{
    windowWidth = width;
    windowHeight = height;
    _listenedKeys = {GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D,
        GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_LEFT};

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Uncomment if you use Mac OS X
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    // Set a callback for resizing the window
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);

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


void Application::destroy(){
    glfwTerminate();
    Logger::log("Application closed", info);
}

bool Application::isKeyPressed(int key)
{
    return currentKeys.contains(key);
}
#include <Application.h>
#include <iostream>

void glfwError(int id, const char* description)
{
    std::cout << "GLFW error: " << description << std::endl;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Application::Application(){
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Uncomment if you use Mac OS X
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwSetErrorCallback(&glfwError);

    // Create GLFW window
    _window = glfwCreateWindow(_startWindowWidth, _startWindowHeight, "Drone simulator", nullptr, nullptr);
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
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Set size of the rendering window
    glViewport(0, 0, _startWindowWidth, _startWindowHeight);

    // Set a callback for resizing the window
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
}

bool Application::isActive()
{
    return !glfwWindowShouldClose(_window);
}

void Application::update()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}


Application::~Application(){
    glfwTerminate();
}
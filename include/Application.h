#pragma once
#include <glad/glad.h>
#include <mutex>
#include <string>
#include <unordered_set>
#include <GLFW/glfw3.h>
#include <array>


class Application{
    GLFWwindow* _window;
    const std::array<int, 9> _listenedKeys = {
        GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D,
        GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_LEFT};

public:
    std::mutex mutex;
    std::unordered_set<int> currentKeys;
    float windowWidth, windowHeight;
    bool firstMouseMove;
    float lastMouseX, lastMouseY;
    float xMoveOffset, yMoveOffset, scrollOffset;
    bool isMouseMoved = false, isMouseScrolled = false;

    Application(int windowWidth, int windowHeight, const std::string& windowName);
    Application(const Application&) = delete;
    bool isActive();
    void update();
    void getKeys();
    void close();
    bool isKeyPressed(int key);
    ~Application();
};

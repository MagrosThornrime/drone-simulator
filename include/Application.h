#pragma once
#include <mutex>
#include <string>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


class Application{
  inline static GLFWwindow* _window;
  inline static std::vector<int> _listenedKeys;

public:

  inline static std::mutex mutex;
  inline static std::unordered_set<int> currentKeys;
  inline static float windowWidth, windowHeight;
  inline static bool firstMouseMove;
  inline static float lastMouseX, lastMouseY;
  inline static float xMoveOffset, yMoveOffset, scrollOffset;
  inline static bool isMouseMoved = false, isMouseScrolled = false;



  static void initialize(int windowWidth, int windowHeight, const std::string& windowName);

  static bool isActive();

  static void update();

  static void getKeys();

  static void close();

  static bool isKeyPressed(int key);

  static void destroy();

};

#pragma once
#include <string>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Application{
  inline static float _windowWidth, _windowHeight;
  inline static GLFWwindow* _window;
  inline static std::vector<int> _listenedKeys;

public:

  inline static std::unordered_set<int> currentKeys;

  static void initialize(int windowWidth, int windowHeight, const std::string& windowName);

  static bool isActive();

  static void update();

  static void getKeys();

  static void close();

  static bool isKeyPressed(int key);

  static void destroy();

  static void setWindowSize(int width, int height);

  static float getWindowWidth() { return _windowWidth; }
  static float getWindowHeight() { return _windowHeight; }
};

#pragma once
#include <array>
#include <unordered_set>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Application{
  const int _startWindowWidth = 800;
  const int _startWindowHeight = 600;
  GLFWwindow* _window{};
  std::array<int, 1> _listenedKeys = {GLFW_KEY_ESCAPE};

public:

  std::unordered_set<int> currentKeys;

  Application();

  bool isActive();

  void update();

  void getKeys();

  void close();

  bool isKeyPressed(int key);

  ~Application();
};

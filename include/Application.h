#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Application{
  const int _startWindowWidth = 800;
  const int _startWindowHeight = 600;
  GLFWwindow* _window{};

public:
  Application();

  void run();

  bool isActive();

  void update();

  ~Application();
};

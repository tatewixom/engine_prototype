#pragma once

#include "libs.h"

class Engine
{
private:

public:
  void initialize();
  void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
  bool loadShaders(GLuint& program);
  void processInput(GLFWwindow* window);
  void render();
  void cleanUp();
  void run();

  GLFWwindow* window;
  GLuint core_program;
};


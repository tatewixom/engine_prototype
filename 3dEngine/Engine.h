#pragma once

#include "libs.h"

class Engine
{
private:

public:
  //framebuffer_resize_callback exists here
  void initialize();
  bool loadShaders(GLuint& program);
  void processInput(GLFWwindow* window);
  void render();
  void cleanUp();
  void run();

  //member variables
  GLFWwindow* window;
  GLuint core_program;
};


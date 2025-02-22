#pragma once

#include "libs.h"

class Engine
{
private:

public:
  //non-class functions pre-exist here

  void initialize();
  bool loadShaders(GLuint& program);
  void processInput(GLFWwindow* window);
  void render();
  void cleanUp();
  void run();

  //member variables
  GLFWwindow* window{};
  GLuint core_program{};

  //buffer arrays
  GLuint VAO{};
  GLuint VBO{};
  GLuint EBO{};

  //texture members
  GLuint texture0{};
  GLuint texture1{};

  //matrix members
};


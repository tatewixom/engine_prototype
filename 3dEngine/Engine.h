#pragma once

#include "State.h"
#include "Play.h"
#include "MainMenu.h"
#include "Pause.h"

class Engine
{
private:

public:
  Engine() = default;
  ~Engine() = default;
  //non-class functions pre-exist here

  void initialize();
  void processInput();
  void update();
  void render();
  void cleanUp();
  void run();

  //VAR
  GLFWwindow* window{};

  //class objects
  State state{};
};


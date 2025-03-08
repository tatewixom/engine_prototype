#pragma once

#include "State.h"
#include "Window.h"

//The mother of all classes. Main caller and game loop reside within here
class Engine
{
private:

public:
  Engine() = default;
  ~Engine() = default;

  //non-class functions pre-exist here

  void initialize();
  void update();
  void render();
  void cleanUp();
  void run();

  //Main window object for all updating and rendering
  GLFWwindow* window{};

  //Engine object for calling all game related functions
  State state{};
};


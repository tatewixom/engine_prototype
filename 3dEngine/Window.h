#pragma once

#include "State.h"
#include "MainMenu.h"

//Class for managing the initialization of the window 
class Window : public StateBase
{
public:
  explicit Window(State& manager) : StateBase(manager) {}
  ~Window() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
  void terminateWindow(GLFWwindow*& window) override;
};


#pragma once

#include "State.h"
#include "MainMenu.h"
#include "Temp.h"

//Class made as the tunnel between settings, gameplay, and the main menu
class Pause : public StateBase
{
public:
  explicit Pause(State& manager) : StateBase(manager) {}
  ~Pause() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
  void terminateWindow(GLFWwindow*& window) override;
};


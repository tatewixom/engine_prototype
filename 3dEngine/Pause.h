#pragma once

#include "State.h"
#include "MainMenu.h"

class Pause : public StateBase
{
public:
  explicit Pause(State& manager) : StateBase(manager) {}
  ~Pause() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


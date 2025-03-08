#pragma once

#include "State.h"

//Class made directly for cutscenes and displaying cinematics
class Cutscene : public StateBase
{
public:
  explicit Cutscene(State& manager) : StateBase(manager) {}
  ~Cutscene() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
  void terminateWindow(GLFWwindow*& window) override;
};


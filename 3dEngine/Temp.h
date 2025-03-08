#pragma once

#include "State.h"

//Class made as a placeholder for need of a state that is dormant 
class Temp : public StateBase
{
public:
  explicit Temp(State& manager) : StateBase(manager) {}
  ~Temp() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
  void terminateWindow(GLFWwindow*& window) override;
};


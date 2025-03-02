#pragma once

#include "State.h"
#include "Play.h"

class Cutscene : public StateBase
{
public:
  explicit Cutscene(State& manager) : StateBase(manager) {}
  ~Cutscene() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


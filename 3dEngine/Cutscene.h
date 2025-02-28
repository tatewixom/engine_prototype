#pragma once

#include "State.h"

class Cutscene : public StateBase
{
public:
  Cutscene() = default;
  ~Cutscene() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


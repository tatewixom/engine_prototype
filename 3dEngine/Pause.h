#pragma once

#include "State.h"

class Pause : public StateBase
{
public:
  Pause() = default;
  ~Pause() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


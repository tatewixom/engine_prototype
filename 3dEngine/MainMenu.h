#pragma once

#include "State.h"

class MainMenu : public StateBase
{
public:
  MainMenu() = default;
  ~MainMenu() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


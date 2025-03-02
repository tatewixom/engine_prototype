#pragma once

#include "State.h"
#include "Play.h"
#include "IPM.h"

class MainMenu : public StateBase
{
public:
  explicit MainMenu(State& manager) : StateBase(manager) {}
  ~MainMenu() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


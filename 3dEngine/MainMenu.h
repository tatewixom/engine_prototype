#pragma once

#include "State.h"
#include "IPM.h"
#include "Play.h"
#include "Temp.h"
#include "Save.h"

//Initial class loaded in at start up and is the gateway to all pathways
class MainMenu : public StateBase
{
public:
  explicit MainMenu(State& manager) : StateBase(manager) {}
  ~MainMenu() = default;

  void initialize(GLFWwindow*& window) override;
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
  void terminateWindow(GLFWwindow*& window) override;
};


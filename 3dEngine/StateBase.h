#pragma once

#include <glew.h>
#include <glfw3.h>

class State;

//Base class of all states and is a pure virtual class
class StateBase
{
protected:
  State& stateManager;

public:
  explicit StateBase(State& manager) : stateManager(manager) {}
  virtual ~StateBase() = default;

  virtual void initialize(GLFWwindow*& window) = 0;
  virtual void update(GLFWwindow*& window) = 0;
  virtual void render(GLFWwindow*& window) = 0;
  virtual void cleanUp(GLFWwindow*& window) = 0;
  virtual void terminateWindow(GLFWwindow*& window) = 0;
};
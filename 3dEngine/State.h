#pragma once

#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <stack>
#include <memory>

class Pause;
class Play;
class Cutscene;
class MainMenu;

class StateBase
{
public:
  virtual ~StateBase() = default;

  virtual void initialize(GLFWwindow*& window) = 0;
  virtual void update(GLFWwindow*& window) = 0;
  virtual void render(GLFWwindow*& window) = 0;
  virtual void cleanUp(GLFWwindow*& window) = 0;
};

class State
{
private:
   std::stack<std::unique_ptr<StateBase>> stateStack;

public:
  State() = default;
  ~State() = default;

  void pushState(std::unique_ptr<StateBase> state);
  void popState();
  void initialize(GLFWwindow*& window);
  void update(GLFWwindow*& window);
  void render(GLFWwindow*& window);
  void cleanUp(GLFWwindow*& window);
  void processStateChanges();
  bool isEmpty() const;
};

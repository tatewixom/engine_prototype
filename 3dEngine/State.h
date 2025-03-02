#pragma once

#include "StateBase.h"

#include <iostream>
#include <stack>
#include <memory>

class State
{
private:
  std::stack<std::unique_ptr<StateBase>> stateStack;

public:
  State() = default;
  ~State() = default;

  void cleanUpPush(GLFWwindow*& window, std::unique_ptr<StateBase> newState);
  void pushInitialize(GLFWwindow*& window, std::unique_ptr<StateBase> newState);
  void clearPush(std::unique_ptr<StateBase> newState);
  void changeState(std::unique_ptr<StateBase> newState);
  void pushState(std::unique_ptr<StateBase> newState);
  void popState();
  void initialize(GLFWwindow*& window);
  void update(GLFWwindow*& window);
  void render(GLFWwindow*& window);
  void cleanUp(GLFWwindow*& window);
  bool isEmpty() const;
};

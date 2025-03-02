#include "State.h"

//STATE FUNCTIONS

void State::cleanUpPush(GLFWwindow*& window, std::unique_ptr<StateBase> newState)
{
  if (!stateStack.empty())
  {
    stateStack.top()->cleanUp(window);
    stateStack.pop();
    stateStack.push(std::move(newState));
  }
}

void State::pushInitialize(GLFWwindow*& window, std::unique_ptr<StateBase> newState)
{
  if (!stateStack.empty())
  {
    stateStack.push(std::move(newState));
    stateStack.top()->initialize(window);
  }
}

void State::clearPush(std::unique_ptr<StateBase> newState)
{
  std::cout << "Clearing States...\n";
  while (!stateStack.empty())
  {
    stateStack.pop();
  }
  stateStack.push(std::move(newState));
}

void State::changeState(std::unique_ptr<StateBase> newState)
{
  if (!stateStack.empty())
  {
    stateStack.pop();
  }
  stateStack.push(std::move(newState));
}

void State::pushState(std::unique_ptr<StateBase> newState)
{
  stateStack.push(std::move(newState));
}

void State::popState()
{
  if (!stateStack.empty())
  {
    stateStack.pop();
  }
}

void State::initialize(GLFWwindow*& window)
{
  if (!stateStack.empty())
  {
    stateStack.top()->initialize(window);
  }
}

void State::update(GLFWwindow*& window)
{
  if (!stateStack.empty())
  {
    stateStack.top()->update(window);
  }
}

void State::render(GLFWwindow*& window)
{
  if (!stateStack.empty())
  {
    stateStack.top()->render(window);
  }
}

void State::cleanUp(GLFWwindow*& window)
{
  if (!stateStack.empty())
  {
    stateStack.top()->cleanUp(window);
  }
}

bool State::isEmpty() const
{
  return stateStack.empty();
}
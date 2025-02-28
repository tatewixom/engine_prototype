#include "State.h"

//STATE FUNCTIONS

void State::pushState(std::unique_ptr<StateBase> state)
{
  stateStack.push(std::move(state));
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
  processStateChanges();
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

void State::processStateChanges()
{
  
}

bool State::isEmpty() const
{
  return stateStack.empty();
}
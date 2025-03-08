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
  else
  {
    std::cerr << "ERROR::STATE.CPP::CLEANUPPUSH::STACK_IS_EMPTY\n";
  }
}

void State::pushInitialize(GLFWwindow*& window, std::unique_ptr<StateBase> newState)
{
  stateStack.push(std::move(newState));
  if (!stateStack.empty())
  {
     stateStack.top()->initialize(window);
  }
  else
  {
     std::cerr << "ERROR::STATE.CPP::PUSHINITIALIZE::STACK_EMPTY_AFTER_PUSH\n";
  }
}

void State::popInitialize(GLFWwindow*& window, std::unique_ptr<StateBase> newState)
{
  if (!stateStack.empty())
  {
    stateStack.pop();
  }
  stateStack.push(std::move(newState));
  stateStack.top()->initialize(window);
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

void State::terminateWindow(GLFWwindow*& window)
{
  if (!stateStack.empty())
  {
    stateStack.top()->terminateWindow(window);
  }
}

void State::stackCleanUp(GLFWwindow*& window, std::unique_ptr<StateBase> newState)
{
  std::cout << "Cleaning & Clearing States...\n";
  while (!stateStack.empty())
  {
  stateStack.top()->cleanUp(window);
  stateStack.pop();
  }
  if (stateStack.empty())
  {
    std::cout << "Finished Cleaning Stack...\n";
    stateStack.push(std::move(newState));
  }
  else
  {
    std::cerr << "ERROR::STATE.CPP::STACKCLEANUP::STACK_FAILED_TO_CLEAN\n";
  }
}

void State::stackCleanUp(GLFWwindow*& window)
{
  std::cout << "Cleaning & Clearing States...\n";
  if (stateStack.empty())
  {
    std::cout << "Stack Already empty...\n";
    return;
  }
  while (!stateStack.empty())
  {
    stateStack.top()->cleanUp(window);
    stateStack.pop();
  }
  if (stateStack.empty())
  {
    std::cout << "Finished Cleaning Stack...\n";
  }
  else
  {
    std::cerr << "ERROR::STATE.CPP::STACKCLEANUP::STACK_FAILED_TO_CLEAN\n";
  }
}

void State::changeCurrentID(int id)
{
  idNumber = id;
}

int State::getCurrentID() const
{
  return idNumber;
}

bool State::isEmpty() const
{
  return stateStack.empty();
}
#pragma once

#include "StateBase.h"

#include <iostream>
#include <stack>
#include <memory>

//Main manager of all states and acts as a mediator between states
class State
{
private:
  //Main stack of all states and private member of State class
  std::stack<std::unique_ptr<StateBase>> stateStack;

  //Integer for communicating cutscene ID's 
  int idNumber{ 0 };

public:
  State() = default;
  ~State() = default;

  //Cleans up state at top of stack, pops, and pushes new state
  void cleanUpPush(GLFWwindow*& window, std::unique_ptr<StateBase> newState);

  //Pushes new state and immediately calls initialization function
  void pushInitialize(GLFWwindow*& window, std::unique_ptr<StateBase> newState);

  //Clears entire state stack (without cleaning) and pushes new state
  void clearPush(std::unique_ptr<StateBase> newState);
  
  //Pops current top of stack and pushes new state
  void changeState(std::unique_ptr<StateBase> newState);

  //Pushes new state to top of stack stack
  void pushState(std::unique_ptr<StateBase> newState);

  //Pops top of stack (doesn't clean)
  void popState();

  //Calls current state's update function
  void initialize(GLFWwindow*& window);

  //Calls current state's update function
  void update(GLFWwindow*& window);

  //Calls current state's render function
  void render(GLFWwindow*& window);

  //Calls current state's clean up function
  void cleanUp(GLFWwindow*& window);

  void terminateWindow(GLFWwindow*& window);

  //Calls each state's clean up function on the stack and pops until there are no states
  void stackCleanUp(GLFWwindow*& window, std::unique_ptr<StateBase> newState);

  //Calls each state's clean up function on the stack and pops until there are no states (this overload doesn't push a new state)
  void stackCleanUp(GLFWwindow*& window);

  //Change the ID to whatever cutscene is needed
  void changeCurrentID(int id);

  //ID used for determining what cutscene to direct to
  int getCurrentID() const;

  //Detecting whether the stack is empty or not
  bool isEmpty() const;
};
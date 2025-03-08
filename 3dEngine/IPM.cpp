#include "IPM.h"

bool IPM::isKeyPressed(GLFWwindow*& window, int key)
{
  return glfwGetKey(window, key) == GLFW_PRESS;
}

bool IPM::isKeyJustPressed(GLFWwindow*& window, int key)
{
  //stores previous key state
  static std::unordered_map<int, bool> keyStates;
  bool currentlyPressed = isKeyPressed(window, key);

  //if key was released before and is now pressed
  if (currentlyPressed && !keyStates[key])
  {
    keyStates[key] = true;
    return true;
  }

  if (!currentlyPressed)
  {
    keyStates[key] = false;
  }

  return false;
}
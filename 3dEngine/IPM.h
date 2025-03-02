#pragma once

#include "glfw3.h"
#include <unordered_map>

class IPM
{
public:
  static bool isKeyPressed(GLFWwindow*& window, int key)
  {
    return glfwGetKey(window, key) == GLFW_PRESS;
  }

  static bool isKeyJustPressed(GLFWwindow*& window, int key)
  {
    //store previous key state
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
};


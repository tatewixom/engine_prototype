#pragma once

#include "glfw3.h"

#include <unordered_map>

//Class made for managing and accessing input functions
class IPM
{
public:
  //Checks if the key is currently being pressed and will allow for repeat of input
  static bool isKeyPressed(GLFWwindow*& window, int key);
  
  //Checks if the key was just released, doesn't allow for repeat input
  static bool isKeyJustPressed(GLFWwindow*& window, int key);
};


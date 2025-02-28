#include "Pause.h"

void Pause::initialize(GLFWwindow*& window)
{

}

void Pause::update(GLFWwindow*& window)
{
  glfwPollEvents();

  if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
  {
    
  }
}

void Pause::render(GLFWwindow*& window)
{
  //DRAW CLEAR 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //nothing to render

  //END DRAW
  glfwSwapBuffers(window);
  glFlush();
}

void Pause::cleanUp(GLFWwindow*& window)
{

}

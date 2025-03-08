#include "Temp.h"

void Temp::initialize(GLFWwindow*& window)
{

}

void Temp::update(GLFWwindow*& window)
{

}

void Temp::render(GLFWwindow*& window)
{
  //DRAW CLEAR 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //nothing to render

  //END DRAW
  glfwSwapBuffers(window);
  glFlush();
}

void Temp::cleanUp(GLFWwindow*& window)
{

}

void Temp::terminateWindow(GLFWwindow*& window)
{
  //end of program
  glfwDestroyWindow(window);
  glfwTerminate();
}
#include "Cutscene.h"

void Cutscene::initialize(GLFWwindow*& window)
{

}

void Cutscene::update(GLFWwindow*& window)
{
  if (IPM::isKeyJustPressed(window, GLFW_KEY_1))
  {
    std::cout << "Closing Window...\n";
    glfwSetWindowShouldClose(window, true);
  }
}

void Cutscene::render(GLFWwindow*& window)
{
  //DRAW CLEAR 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //nothing to render

  //END DRAW
  glfwSwapBuffers(window);
  glFlush();
}

void Cutscene::cleanUp(GLFWwindow*& window)
{

}

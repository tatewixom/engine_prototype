#include "Pause.h"

void Pause::initialize(GLFWwindow*& window)
{

}

void Pause::update(GLFWwindow*& window)
{
  glfwPollEvents();

  if (IPM::isKeyJustPressed(window, GLFW_KEY_1))
  {
    std::cout << "Closing Window...\n";
    stateManager.stackCleanUp(window, std::make_unique<Temp>(stateManager));
    glfwSetWindowShouldClose(window, true);
  }
  if (IPM::isKeyJustPressed(window, GLFW_KEY_M))
  {
    stateManager.clearPush(std::make_unique<MainMenu>(stateManager));
    std::cout << "Entering Menu State...\n";
  }
  else if (IPM::isKeyJustPressed(window, GLFW_KEY_ESCAPE))
  {
    std::cout << "Entering Play State...\n";
    stateManager.popState();
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

void Pause::terminateWindow(GLFWwindow*& window)
{
  
}

#include "MainMenu.h"

//NON-CLASS FUNCTIONS

void MainMenu::initialize(GLFWwindow*& window)
{
  
}

void MainMenu::update(GLFWwindow*& window)
{
  glfwPollEvents();

  if (IPM::isKeyJustPressed(window, GLFW_KEY_1))
  {
    std::cout << "Closing Window...\n";
    stateManager.stackCleanUp(window, std::make_unique<Temp>(stateManager));
    glfwSetWindowShouldClose(window, true);
  }
  if (IPM::isKeyJustPressed(window, GLFW_KEY_ENTER))
  {
    std::cout << "Entering Play State...\n";
    stateManager.pushInitialize(window, std::make_unique<Play>(stateManager));
  }

}

void MainMenu::render(GLFWwindow*& window)
{
  //DRAW CLEAR 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //nothing to render

  //END DRAW
  glfwSwapBuffers(window);
  glFlush();
}

void MainMenu::cleanUp(GLFWwindow*& window)
{
  //nothing to clean up
}

void MainMenu::terminateWindow(GLFWwindow*& window)
{
  //end of program
  glfwDestroyWindow(window);
  glfwTerminate();
}

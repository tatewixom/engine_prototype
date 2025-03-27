#include "MainMenu.h"

//NON-CLASS FUNCTIONS

void MainMenu::initialize(GLFWwindow*& window)
{
  //Confirming save state files are not deleted and creating new ones if so
   
  //Vector containing names of all save files and creates new files if they are deleted
  std::vector<std::string> saveFiles;

  const std::string save_player{ "SaveStates/save_player.txt" };
  saveFiles.push_back(save_player);

  const std::string save_env{ "SaveStates/save_environment.txt" };
  saveFiles.push_back(save_env);

  const std::string save_enemy{ "SaveStates/save_enemy.txt" };
  saveFiles.push_back(save_enemy);

  Save save;
  for (int i{ 0 }; i < saveFiles.size(); i++)
  {
    if (!save.exists(saveFiles[i]))
    {
      std::cout << saveFiles[i] << " doesn't exist\n" << "Creating new file...\n";
      save.create(saveFiles[i]);
      save.write(saveFiles[i], "comatosed;");
    }
  }
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

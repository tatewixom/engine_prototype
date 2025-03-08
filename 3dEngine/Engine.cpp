#include "Engine.h"

void Engine::initialize()
{
  state.changeState(std::make_unique<MainMenu>(state));
  state.initialize(window);
}

void Engine::update()
{
  state.update(window);
}

void Engine::render()
{
  state.render(window);
}

void Engine::cleanUp()
{
  state.terminateWindow(window);
  state.stackCleanUp(window);
}

void Engine::run()
{
  initialize();

  while (!glfwWindowShouldClose(window))
  {
    update();
    
    render();
  }
  
  std::cout << "Game Exiting...\n";
  cleanUp();
}

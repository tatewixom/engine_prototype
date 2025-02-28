#include "Engine.h"

void Engine::initialize()
{
  state.pushState(std::make_unique<MainMenu>());
  state.initialize(window);
}

void Engine::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
  {
    state.pushState(std::make_unique<Play>());
    state.initialize(window);
  }
  if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
  {
    state.pushState(std::make_unique<Pause>());
    state.initialize(window);
  }
}

void Engine::update()
{
  processInput();
  state.update(window);
}

void Engine::render()
{
  state.render(window);
}

void Engine::cleanUp()
{
  state.cleanUp(window);
}

void Engine::run()
{
  initialize();

  while (!glfwWindowShouldClose(window))
  {
    update();

    render();
  }

  cleanUp();
}

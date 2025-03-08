#include "Window.h"

void static framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
  glViewport(0, 0, fbW, fbH);
}

void Window::initialize(GLFWwindow*& window)
{
  std::cout << "Initializing Window...\n";
  //INIT GLFW
  glfwInit();

  //CREATE WINDOW
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); enable if using on MACOS

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL_Project", NULL, NULL);

  if (window == NULL)
  {
    std::cerr << "ERROR::GLFWWINDOW::FAILED_TO_CREATE_WINDOW" << '\n';
    glfwTerminate();
  }

  //glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

  //disabled, enable only if screen is not resizable.
  //glViewport(0, 0, framebufferWidth, framebufferHeight);

  glfwMakeContextCurrent(window); //IMPORTANT for glew

  //INIT GLEW (glew needs window and opengl context)
  glewExperimental = GL_TRUE;

  //error
  if (glewInit() != GLEW_OK)
  {
    std::cerr << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << '\n';
    glfwTerminate();
  }

  //OPENGL OPTIONS

  //allows us to "access" z coords
  glEnable(GL_DEPTH_TEST);
  //allows us to not render unused faces
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  //defining what the front face is in terms of vectors
  glFrontFace(GL_CCW);
  //allows for blending colors
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glDisable(GL_LIGHTING);

  std::cout << "Entering Menu State...\n";
  //pushing initial state
  stateManager.popInitialize(window, std::make_unique<MainMenu>(stateManager));
}

void Window::update(GLFWwindow*& window)
{

}

void Window::render(GLFWwindow*& window)
{
  //DRAW CLEAR 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //nothing to render

  //END DRAW
  glfwSwapBuffers(window);
  glFlush();
}

void Window::cleanUp(GLFWwindow*& window)
{

}

void Window::terminateWindow(GLFWwindow*& window)
{
  //end of program
  glfwDestroyWindow(window);
  glfwTerminate();
}

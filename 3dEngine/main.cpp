#include "libs.h"

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
  glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint& program)
{
  bool loadSuccess = true;
  char infoLog[512];
  GLint success;

  std::string temp = "";
  std::string src = "";

  std::ifstream in_file;

  //vertex
  in_file.open("vertex_core.glsl");

  if (in_file.is_open())
  {
    while (std::getline(in_file, temp))
    {
      src += temp + "\n";
    }
  }
  else
  {
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << std::endl;
    loadSuccess = false;
  }

  in_file.close();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  const GLchar* vertSrc = src.c_str();
  glShaderSource(vertexShader, 1, &vertSrc, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << std::endl;
    std::cerr << infoLog << std::endl;
    loadSuccess = false;
  }
  
  temp = "";
  src = "";

  //fragment
  in_file.open("fragment_core.glsl");

  if (in_file.is_open())
  {
    while (std::getline(in_file, temp))
    {
      src += temp + "\n";
    }
  }
  else
  {
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << std::endl;
    loadSuccess = false;
  }

  in_file.close();

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  const GLchar* fragSrc = src.c_str();
  glShaderSource(fragmentShader, 1, &fragSrc, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << std::endl;
    std::cerr << infoLog << std::endl;
    loadSuccess = false;
  }

  temp = "";
  src = "";

  //program
  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << std::endl;
    std::cerr << infoLog << std::endl;
    loadSuccess = false;
  }

  //end
  glUseProgram(0);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return loadSuccess;
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

int main()
{
  //init glfw
  glfwInit();

  //create window
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 600;
  int framebufferWidth = 0;
  int framebufferHeight = 0;

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); enable if using on MACOS

  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL_Project", NULL, NULL);

  if (window == NULL)
  {
    std::cerr << "ERROR::GLFWWINDOW::FAILED_TO_CREATE_WINDOW" << std::endl;
    glfwTerminate();
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

  //disabled, enable only if screen is not resizable.
  //glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  //glViewport(0, 0, framebufferWidth, framebufferHeight);

  glfwMakeContextCurrent(window); //IMPORTANT for glew

  //init glew (glew needs window and opengl context)
  glewExperimental = GL_TRUE;

  //error
  if (glewInit() != GLEW_OK)
  {
    std::cerr << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << std::endl;
    glfwTerminate();
  }

  //shader init
  GLuint core_program;
  if (!loadShaders(core_program))
  {
    glfwTerminate();
  }

  //main loop
  while (!glfwWindowShouldClose(window))
  {
    //update input
    glfwPollEvents();
    processInput(window);

    //update

    //draw clear 
    glClearColor(0.2f, 0.3f, 0.3f, 1.f); //works in RGBA format
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //draw

    //end draw
    glfwSwapBuffers(window);
    glFlush();
  }


  //end of program
  glfwDestroyWindow(window);
  glfwTerminate();

  //delete program
  glDeleteProgram(core_program);

  return 0;
}

//test hehe
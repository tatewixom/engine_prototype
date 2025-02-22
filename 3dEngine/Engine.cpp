#include "Engine.h"

//non-class functions/arrays

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
{
  glViewport(0, 0, fbW, fbH);
}

Vertex vertices[] =
{
  //triangle 1
  //position                      //color                     //texcoords
  glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),
  glm::vec3(-0.5f ,-0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),
  glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),

  //triangle 2
  //glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),
  //glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),
  glm::vec3(0.5f, 0.5f, 0.f),     glm::vec3(1.f, 1.f, 0.f),   glm::vec2(0.f, 0.f)
  
};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

//helps with overlapping points, by telling which points to use so there's less points used
GLuint indices[] =
{
  0, 1, 2, //triangle 1

  0, 2, 3 // triangle 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

//engine class functions

void Engine::initialize()
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

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL_Project", NULL, NULL);

  if (window == NULL)
  {
    std::cerr << "ERROR::GLFWWINDOW::FAILED_TO_CREATE_WINDOW" << '\n';
    glfwTerminate();
  }

  //error at framebuffer_resize don't know why. works in main.cpp for whatever reason
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
    std::cerr << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << '\n';
    glfwTerminate();
  }

  //opengl options
  
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

  //shader init
  if (!loadShaders(core_program))
  {
    glfwTerminate();
  }

  //model

  //VAO, VBO, EBO; these are buffers that hold data to send to graphics card memory
  //initialize VAO; Vertex Array Object
  
  //generate VAO; '1' means we are creating 1 buffer; basically ID to the buffer
  glCreateVertexArrays(1, &VAO);
  //bind VAO
  glBindVertexArray(VAO);

  //VBO; Vertex Buffer Object
 
  //generate VBO
  glGenBuffers(1, &VBO);
  //bind VBO
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //send array of floats to the graphics card; static, wont change much
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //EBO; Element Buffer Object
  
  //this will send different type of array, this is used for indexing vertices
  glGenBuffers(1, &EBO);
  //bind EBO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  //sending index of vertices to graphics
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  //set VertexAttribPointer and enable (input assembly); at location 0
  //GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
  glEnableVertexAttribArray(0);
  //color; at location 1
  //attribLoc = glGetAttribLocation(core_program, "vertex_color");
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
  glEnableVertexAttribArray(1);
  //texcoords; at location 2
  //attribLoc = glGetAttribLocation(core_program, "vertex_color");
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
  glEnableVertexAttribArray(2);

  //bind VAO 0
  glBindVertexArray(0);
}

bool Engine::loadShaders(GLuint& program)
{
  bool loadSuccess = true;
  char infoLog[512];
  GLint success;

  std::string temp{};
  std::string src{};

  std::ifstream in_file;

  //vertex
  in_file.open("vertex_core.glsl");

  //keep in mind that the vertex core flips the image along the y axis (line 15)
  if (in_file.is_open())
  {
    while (std::getline(in_file, temp))
    {
      src += temp + "\n";
    }
  }
  else
  {
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << '\n';
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
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << '\n';
    std::cerr << infoLog << '\n';
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
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << '\n';
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
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << '\n';
    std::cerr << infoLog << '\n';
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
    std::cerr << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << '\n';
    std::cerr << infoLog << '\n';
    loadSuccess = false;
  }

  //end
  glUseProgram(0);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return loadSuccess;
}

void Engine::processInput(GLFWwindow* window)
{
  glfwPollEvents();

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

void Engine::render()
{
  //draw clear 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //define what program to use
  glUseProgram(core_program);

  //bind vertex array object
  glBindVertexArray(VAO);

  //draw; define what index we want to start drawing from
  //glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);    //does the same thing, but doesn't use indices
  glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

  //end draw
  glfwSwapBuffers(window);
  glFlush();
}

void Engine::cleanUp()
{
  //end of program
  glfwDestroyWindow(window);
  glfwTerminate();

  //delete program
  glDeleteProgram(core_program);
}

void Engine::run()
{
  initialize();

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    render();
  }

  cleanUp();
}

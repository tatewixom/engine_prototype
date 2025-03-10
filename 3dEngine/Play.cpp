#include "Play.h"

//STRUCTS

struct Vertex
{
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texcoord;
  glm::vec3 normal;
};

//NON-CLASS ARRAYS

Vertex vertices[] =
{
  //triangle 1
  //position                      //color                     //texcoords
  glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),    glm::vec3(0.f, 0.f, -1.f),
  glm::vec3(-0.5f ,-0.5f, 0.f),   glm::vec3(0.f, 1.f, 0.f),   glm::vec2(0.f, 0.f),    glm::vec3(0.f, 0.f, -1.f),
  glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),    glm::vec3(0.f, 0.f, -1.f),

  //triangle 2
  //glm::vec3(-0.5f, 0.5f, 0.f),    glm::vec3(1.f, 0.f, 0.f),   glm::vec2(0.f, 1.f),
  //glm::vec3(0.5f, -0.5f, 0.f),    glm::vec3(0.f, 0.f, 1.f),   glm::vec2(1.f, 0.f),
  glm::vec3(0.5f, 0.5f, 0.f),     glm::vec3(1.f, 1.f, 0.f),   glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, -1.f)

};
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

//helps with overlapping points, by telling which points to use so there's less points used
GLuint indices[] =
{
  0, 1, 2, //triangle 1

  0, 2, 3 // triangle 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

//VARIABLES

GLuint core_program{};

//matrix members
glm::mat4 ModelMatrix(1.f);

glm::mat4 ViewMatrix(1.f);
glm::vec3 camPosition(0.f, 0.f, 1.f);
glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);

float fov = 90.f;
float nearPlane = 0.1f;
float farPlane = 1000.f;
glm::mat4 ProjectionMatrix(1.f);

glm::vec3 position(0.f);
glm::vec3 rotation(0.f);
glm::vec3 scale(1.f);

glm::vec3 lightPos0(0.f, 0.f, 0.f);

//window members
int framebufferWidth = 0;
int framebufferHeight = 0;

//buffer arrays
GLuint VAO{};
GLuint VBO{};
GLuint EBO{};

//texture members
GLuint texture0{};
GLuint texture1{};

//CLASS FUNCTIONS

void Play::initialize(GLFWwindow*& window)
{
  //SHADER INIT
  if (!loadShaders(core_program))
  {
    glfwTerminate();
  }

  //MODEL

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
  //normal; at location 3
  //attribLoc = glGetAttribLocation(core_program, "vertex_color");
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
  glEnableVertexAttribArray(3);

  //bind VAO 0
  glBindVertexArray(0);

  //TEXTURE INIT

  //texture 0
  int image_width{};
  int image_height{};
  unsigned char* image = SOIL_load_image("Assets/Images/cialogo.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

  glGenTextures(1, &texture0);
  glBindTexture(GL_TEXTURE_2D, texture0);

  //S and T are basically other names for X and Y
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //some type of antialiasing when changing size of texture; MAG = Magnification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //another filter being applied when making an image smaller; MIN = Minification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  //checks to see if there is even a texture to load
  if (image)
  {
    //keep in mind that a char is basically the same as an unsigned byte
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    //Mipmap is when opengl takes your image to make smaller and
    //bigger versions of it to auto-adjust how far away you're looking at picture/object
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cerr << "ERROR::INITIALIZE::TEXTURE_LOADING_FAILED" << '\n';
  }

  //sets to zero for case of no texture needed to render next run
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  //removes image data from memory used in SOIL_load_image call
  SOIL_free_image_data(image);

  //texture 1
  int image_width1{};
  int image_height1{};
  unsigned char* image1 = SOIL_load_image("Assets/Images/cardboard.png", &image_width1, &image_height1, NULL, SOIL_LOAD_RGBA);

  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  //S and T are basically other names for X and Y
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //some type of antialiasing when changing size of texture; MAG = Magnification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  //another filter being applied when making an image smaller; MIN = Minification
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  //checks to see if there is even a texture to load
  if (image1)
  {
    //keep in mind that a char is basically the same as an unsigned byte
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width1, image_height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
    //Mipmap is when opengl takes your image to make smaller and
    //bigger versions of it to auto-adjust how far away you're looking at picture/object
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cerr << "ERROR::INITIALIZE::TEXTURE_LOADING_FAILED2" << '\n';
  }

  //sets to zero for case of no texture needed to render next run
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
  //removes image data from memory used in SOIL_load_image call
  SOIL_free_image_data(image1);

  //INIT MATRIX
  ModelMatrix = glm::translate(ModelMatrix, position);
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f)); //x 
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f)); //y
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f)); //z
  ModelMatrix = glm::scale(ModelMatrix, scale);

  ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

  glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  int product{};
  if (framebufferWidth == 0 && framebufferHeight == 0)
  {
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(product), nearPlane, farPlane);
  }
  else
  {
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth / framebufferHeight), nearPlane, farPlane);
  }

  //INIT UNIFORMS
  glUseProgram(core_program);

  //GL_FALSE is set to false because that is an option for transposing matrices
  glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
  glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
  glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

  glUniform3fv(glGetUniformLocation(core_program, "lightPos0"), 1, glm::value_ptr(lightPos0));

  glUseProgram(0);
}

bool Play::loadShaders(GLuint& program)
{
  bool loadSuccess = true;
  char infoLog[512];
  GLint success;

  std::string temp{};
  std::string src{};

  std::ifstream in_file;

  //VERTEX
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

  //FRAGMENT
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

  //PROGRAM
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

  //END
  glUseProgram(0);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return loadSuccess;
}

void Play::update(GLFWwindow*& window)
{
  glfwPollEvents();

  if (IPM::isKeyJustPressed(window, GLFW_KEY_1))
  {
    std::cout << "Closing Window...\n";
    stateManager.stackCleanUp(window, std::make_unique<Temp>(stateManager));
    glfwSetWindowShouldClose(window, true);
  }
  if (IPM::isKeyJustPressed(window, GLFW_KEY_ESCAPE))
  {
    std::cout << "Entering Pause State...\n";
    stateManager.pushState(std::make_unique<Pause>(stateManager));
  }

  //position
  if (IPM::isKeyPressed(window, GLFW_KEY_W))
  {
    position.z += 0.05f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_A))
  {
    position.x += 0.01f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_S))
  {
    position.z -= 0.05f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_D))
  {
    position.x -= 0.01f;
  }

  //rotation
  if (IPM::isKeyPressed(window, GLFW_KEY_E))
  {
    rotation.z -= 1.f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_Q))
  {
    rotation.z += 1.f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_UP))
  {
    rotation.x -= 1.f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_DOWN))
  {
    rotation.x += 1.f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_LEFT))
  {
    rotation.y -= 1.f;
  }
  if (IPM::isKeyPressed(window, GLFW_KEY_RIGHT))
  {
    rotation.y += 1.f;
  }
}

void Play::render(GLFWwindow*& window)
{
  //DRAW CLEAR 
  glClearColor(0.f, 0.f, 0.f, 1.f); //works in RGBA format
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  //define what program to use
  glUseProgram(core_program);

  //update uniforms; makes it so the variable 'texture0' is assigned a value
  glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);
  glUniform1i(glGetUniformLocation(core_program, "texture1"), 1);

  //move, rotate, and scale
  ModelMatrix = glm::mat4(1.f);
  ModelMatrix = glm::translate(ModelMatrix, position);
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f)); //x 
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f)); //y
  ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f)); //z
  ModelMatrix = glm::scale(ModelMatrix, scale);

  glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));

  glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
  int product{};
  if (framebufferWidth == 0 || framebufferHeight == 0)
  {
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(product), nearPlane, farPlane);
  }
  else
  {
    ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth / framebufferHeight), nearPlane, farPlane);
  }
  glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

  //activate texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture1);

  //bind vertex array object
  glBindVertexArray(VAO);

  //DRAW 
  //define what index we want to start drawing from
  //glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);    //does the same thing, but doesn't use indices
  glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

  //END DRAW
  glfwSwapBuffers(window);
  glFlush();
  //any value 0 basically means resetting
  glBindVertexArray(0);
  glUseProgram(0);
  glActiveTexture(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Play::cleanUp(GLFWwindow*& window)
{
  //delete program
  glDeleteProgram(core_program);
}

void Play::terminateWindow(GLFWwindow*& window)
{
  //end of program
  glfwDestroyWindow(window);
  glfwTerminate();

  //delete program
  glDeleteProgram(core_program);
}

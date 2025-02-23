#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//glew
#include <glew.h>

//glf
#include <glfw3.h>

//glm
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

//soil2
#include <SOIL2.h>

struct Vertex
{
  glm::vec3 position;
  glm::vec3 color;
  glm::vec2 texcoord;
  glm::vec3 normal;
};
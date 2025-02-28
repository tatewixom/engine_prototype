#pragma once

#include "State.h"

//std
#include <iostream>
#include <fstream>
#include <string>

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

class Play : public StateBase
{
public:
  Play() = default;
  ~Play() = default;

  void initialize(GLFWwindow*& window) override;
  bool loadShaders(GLuint& program);
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
};


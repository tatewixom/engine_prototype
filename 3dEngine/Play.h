#pragma once

#include "State.h"
#include "Pause.h"
#include "CutScene.h"
#include "IPM.h"
#include "Temp.h"

//std
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

//Class representing the play state and carrying out any gameplay functions
class Play : public StateBase
{
public:
  explicit Play(State& manager) : StateBase(manager) {}
  ~Play() = default;

  void initialize(GLFWwindow*& window) override;
  bool loadShaders(GLuint& program);
  void update(GLFWwindow*& window) override;
  void render(GLFWwindow*& window) override;
  void cleanUp(GLFWwindow*& window) override;
  void terminateWindow(GLFWwindow*& window) override;
};


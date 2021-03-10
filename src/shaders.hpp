#pragma once

#include "glad.h"
#include <string>

struct Shader {
  GLuint shaderProgram;
  Shader();
  std::string open_shader(std::string path);
};
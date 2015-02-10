#pragma once

//
// GLFWのWindow管理
//

#include "defines.hpp"
#include <GLFW/glfw3.h>


class GlfwWindow {
  GLFWwindow* window_;


public:
  GlfwWindow(const int width, const int height,
             const bool is_visible = true, const bool is_fullscreen = false);

  ~GlfwWindow();

  // TIPS:このクラスはコピー禁止
  GlfwWindow(const GlfwWindow&) = delete;
  GlfwWindow& operator=(const GlfwWindow&) = delete;

  
  GLFWwindow* const operator()();
  const GLFWwindow* const operator()() const;
  
};

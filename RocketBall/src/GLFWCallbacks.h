#pragma once
#include "Graphics.h"

void WindowResizeCallback(GLFWwindow* window, int width, int height);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void MouseWheelCallback(GLFWwindow* window, double xDelta, double yDelta);
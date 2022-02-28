#include "UI.h"

#include "implementations/imgui_impl.h"

bool UI::isKeyPressed(int keycode) {
  auto window = (GLFWwindow *)_window->getNativeWindow();
  auto state = glfwGetKey(window, keycode);

  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool UI::isMouseButtonPressed(int button) {
  auto window = (GLFWwindow *)_window->getNativeWindow();
  auto state = glfwGetMouseButton(window, button);

  return state == GLFW_PRESS || state == GLFW_REPEAT;
}

std::pair<float, float> UI::getMousePos() {
  auto window = (GLFWwindow *)_window->getNativeWindow();
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  return { (float)xpos, (float)ypos };
}

float UI::getMouseX() {
  return getMousePos().first;
}

float UI::getMouseY() {
  return getMousePos().second;
	}
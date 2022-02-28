#include "Core/Window/Window.h"

// Events
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

// Implementation
#include "implementations/imgui_impl.h"

#include <iostream>

static void glfw_error_callback(int error, const char* description) {
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void Window::setVSync(bool enable) {
  if (enable) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }

  _data.vSync = enable;
}

Window::Window(const Config &config) {
  _data.title = config.title;
  _data.width = config.width;
  _data.height = config.height;

  int glfw_success = 0;
  int glad_success = 0;

  if (!glfw_success) {
    glfw_success = glfwInit();
    if (glfw_success) {
      glfwSetErrorCallback(glfw_error_callback);
    } else {
      std::cout << "Could not initialize glfw" << std::endl;
    }
  }

  _window = glfwCreateWindow((int)config.width, (int)config.height, config.title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(_window);

  if (!glad_success) {
    glad_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!glad_success) {
      std::cout << "Could not initialize glad" << std::endl;;
    }
  }

  glfwSetWindowUserPointer(_window, &_data);
  setVSync(true);

  /**
   * @brief GLFW CallBacks
   * Mouse/Key/Window Events
   */

  glfwSetWindowSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
    Data &data = *(Data *)glfwGetWindowUserPointer(window);
    data.width = width;
    data.height = height;

    WindowResizeEvent event(width, height);
    data.eventCallBack(event);
  });

  glfwSetWindowCloseCallback(_window, [](GLFWwindow *window) {
    Data &data = *(Data *)glfwGetWindowUserPointer(window);
    WindowCloseEvent event;
    data.eventCallBack(event);
  });

  glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
    Data &data = *(Data *)glfwGetWindowUserPointer(window);
    switch (action) {
      case GLFW_PRESS:
        {
          KeyPressedEvent event(key, 0);
          data.eventCallBack(event);
          break;
        }
      
      case GLFW_RELEASE:
        {
          KeyReleasedEvent event(key);
          data.eventCallBack(event);
          break;
        }
      
      case GLFW_REPEAT:
        {
          KeyPressedEvent event(key, 1);
          data.eventCallBack(event);
          break;
        }
    }
  });


  glfwSetMouseButtonCallback(_window, [](GLFWwindow *window, int button, int action, int modes) {
    Data &data = *(Data *)glfwGetWindowUserPointer(window);

    switch (action) {
      case GLFW_PRESS:
        {
          MouseButtonPressedEvent event(button);
          data.eventCallBack(event);
          break;
        }

      case GLFW_RELEASE:
        {
          MouseButtonReleasedEvent event(button);
          data.eventCallBack(event);
          break;
        }
    }
  });

  glfwSetScrollCallback(_window, [](GLFWwindow *window, double xOffset, double yOffset) {
    Data &data = *(Data *)glfwGetWindowUserPointer(window);

    MouseScrolledEvent event((float)xOffset, (float)yOffset);
    data.eventCallBack(event);
  });

  glfwSetCursorPosCallback(_window, [](GLFWwindow *window, double xPos, double yPos) {
    Data &data = *(Data *)glfwGetWindowUserPointer(window);

    MouseMovedEvent event((float)xPos, (float)yPos);
    data.eventCallBack(event);
  });


  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplGlfw_InitForOpenGL(_window, true);
  ImGui_ImplOpenGL3_Init(OPENGL_VERSION);

  if (glad_success && glfw_success) {
    _initialized = true;
  }
}

void Window::preUpdate() {
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void Window::postUpdate() {
  ImGuiIO &io = ImGui::GetIO();
  io.DisplaySize = ImVec2(getWidth(), getHeight());

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }

  glfwPollEvents();
  glfwSwapBuffers(_window);
}

void Window::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(_window);
  glfwTerminate();
}

void *Window::getNativeWindow() {
  return _window;
}
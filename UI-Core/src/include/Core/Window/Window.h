#ifndef UI_CORE_WINDOW_H
#define UI_CORE_WINDOW_H

#include "Core/Events/Event.h"

#define OPENGL_VERSION "#version 460"
#include <string>
#include <functional>

struct GLFWwindow;

class Window {
 public:

  using EventCallBack = std::function<void(Event&)>;

  struct Config {
    std::string title;
    unsigned int width, height;

    Config(const std::string &title = "Window", unsigned int width = 1280, unsigned int height = 720)
      : title(title), width(width), height(height) {
    }
  };

  virtual void preUpdate(); // pre render
  virtual void postUpdate(); // post render

  virtual void shutdown(); // close window/shutdown instance

  virtual unsigned int getWidth() { return _data.width; }
  virtual unsigned int getHeight() { return _data.height; }

  virtual void setEventCallBack(const EventCallBack &callback) {
    _data.eventCallBack = callback;
  }

  virtual void setVSync(bool enable);
  virtual bool isVSync() { return _data.vSync; }

  // virtual bool getCloseWindow();
  virtual void *getNativeWindow();

  Window(const Config &config = Config());

  bool isInitialized() { return _initialized; }

 private:
  GLFWwindow *_window;

  bool _initialized = false;

  struct Data {
    std::string title;
    unsigned int width, height;
    bool vSync;

    EventCallBack eventCallBack;
  };

  Data _data;
};

#endif
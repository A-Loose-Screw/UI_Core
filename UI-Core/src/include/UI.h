#ifndef UI_H
#define UI_H

#include <iostream>
#include <memory>

// Platform window
#include "Platforms/PlatformDetection.h"
#include "Core/Window/Window.h"

// Events
#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/ApplicationEvent.h"

// Input
#include "Core/Input/Input.h"

#include "implementations/imgui_impl.h"

class UI : Input {
 public:
  UI(const std::string &name = "UI-Core", int width = 1280, int height = 720) : _name(name) {
    _config.title = _name;
    _config.width = width;
    _config.height = height;

    _window = std::make_unique<Window>(_config);
    _window->setEventCallBack(BIND_EVENT_FN(UI::onCoreEvent));
  }

  void preUpdate() {
    _window->preUpdate();
  }

  void postUpdate() {
    _window->postUpdate();
  }


  /**
   * @brief Core event controller
   * On Event do something
   * 
   * @param e 
   */
  void onCoreEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(UI::onWindowClose));

    // Check if event is handled somewhere else
    if (!e.handled) {
      onEvent(e);
    }
  }

  /**
   * @brief overridable for users on event
   * 
   * @param e (event)
   */
  virtual void onEvent(Event &e) {}

  bool onWindowClose(WindowCloseEvent &e) {
    _windowClose = true;
    return true;
  }

  bool windowCloseEvent() {
    return _windowClose;
  }

  void shutdown() {
    _window->shutdown();
  }

  Window &getWindow() {
    return *_window;
  }

  virtual bool isKeyPressed(int keycode) override;
  virtual bool isMouseButtonPressed(int button) override;

  virtual float getMouseX() override;
  virtual float getMouseY() override;

  virtual std::pair<float, float> getMousePos() override;

 private:
  std::string _name;
  bool _windowClose = false;
  Window::Config _config;
  std::unique_ptr<Window> _window;
  std::unique_ptr<Input> _input;
};

#endif
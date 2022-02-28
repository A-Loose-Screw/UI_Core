#ifndef UI_INPUT_H
#define UI_INPUT_H

#include <memory>
#include "Core/Core.h"

/**
 * @brief Base class for Inputs, protected members must be overriden
 * 
 */
class Input {
 public:

  virtual bool isKeyPressed(int keycode) = 0;
  virtual bool isMouseButtonPressed(int button) = 0;

  virtual float getMouseX() = 0;
  virtual float getMouseY() = 0;

  virtual std::pair<float, float> getMousePos() = 0;
};

#endif
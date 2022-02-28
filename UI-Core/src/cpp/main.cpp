/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 * Temporary File for testing
 * 
 */

#include <iostream>
#include "UI.h"
#include "implementations/imgui_impl.h"

// Window *window;
UI ui;

float f = 0;

void onUpdate() {

  // Slider
  char buffer[] = "Input Text";
  ImGui::InputText("string", buffer, IM_ARRAYSIZE(buffer));
  ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
}

int main() {
  
  if (!ui.getWindow().isInitialized()) {
    std::cout << "Could not initialize window" << std::endl;
    return -1;
  }

  while (!ui.windowCloseEvent()) {
    ui.preUpdate();
    onUpdate();
    ui.postUpdate();

    if (ui.isKeyPressed(Key::A)) {
      std::cout << "A Pressed" << std::endl;
    }
  }

  ui.shutdown();

  return 0;
}
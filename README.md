# UI_Core
Cross platform UI Core for gradle/cpp projects using imgui

Example Usage
```cpp
#include <UI.h>
#include <Implementations/imgui_impl.h>

UI ui;

float f = 0;

void onUpdate() {
  char buffer[] = "Input Text";
  ImGui::InputText("String", buffer, IM_ARRAYSIZE(buffer));
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
```
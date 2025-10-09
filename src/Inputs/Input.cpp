#include <src/Inputs/Input.h>
#include <src/Inputs/InputSystem.h>

namespace SOUP {

  const InputSystem *Input::s_system = nullptr;
  
  void Input::bind(const InputSystem *system) { s_system = system; }

  void Input::unbind() { s_system = nullptr; }

  bool Input::isKeyHeld(ScanCode scancode) { return s_system->held(static_cast<int>(scancode)); }

  bool Input::isKeyPressed(ScanCode scancode) {
    return s_system->pressed(static_cast<int>(scancode));
  }

  bool Input::isKeyReleased(ScanCode scancode) {
    return s_system->released(static_cast<int>(scancode));
  }
} // namespace SOUP
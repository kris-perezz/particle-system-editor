#pragma once

#include <src/Inputs/InputSystem.h>
#include <src/Inputs/KeyCodes.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  class Input {
    public:
    static void bind(const InputSystem *system);
    static void unbind();
    static bool isKeyHeld(ScanCode scancode);
    static bool isKeyPressed(ScanCode scancode);
    static bool isKeyReleased(ScanCode scancode);
    private:
    static const InputSystem *s_system;
  };
} // namespace SOUP
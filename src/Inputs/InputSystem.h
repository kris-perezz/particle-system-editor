#pragma once

#include <src/SOUP_pch.h>

namespace SOUP {
  class InputSystem {
  public:
    void begin();
    void end();
    void reset();

    bool held(int scancode) const;
    bool pressed(int scancode) const;
    bool released(int scancode) const;

  private:
    const bool *m_currKeyboard = nullptr;
    std::array<uint8_t, SDL_SCANCODE_COUNT> m_prev{};
  };
} // namespace SOUP
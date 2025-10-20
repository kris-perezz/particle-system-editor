#pragma once

#include <chrono>

namespace SOUP {
  class EngineTime {
  public:

    static float getTime() {
      static const auto start = std::chrono::steady_clock::now();
      return std::chrono::duration<float>(std::chrono::steady_clock::now() - start).count();
    }
  };
} // namespace SOUP
#pragma once

#include <src/SOUP_pch.h>

namespace SOUP {
struct WindowProperties {
  std::string title;
  uint32_t width;
  uint32_t height;
  bool vsync;
  bool fullscreen;

  WindowProperties(const std::string title = "Particle System Editor",
                   uint32_t width = 1280,
                   uint32_t height = 720,
                   bool vsync = false,
                   bool fullscreen = false) {
    this->title = title;
    this->width = width;
    this->height = height;
    this->vsync = vsync;
    this->fullscreen = fullscreen;
  };
};

class Window {
public:
  Window(const WindowProperties &properties);

  ~Window();

  void onUpdate();

  uint32_t getWidth();
  uint32_t getHeight();

  bool isVsyncOn();

  void setVsync(bool on);

private:
  void init(const WindowProperties &properties);

  void shutdown();
  SDL_Window *m_window;
  SDL_GLContext m_context;

  WindowProperties m_windowProperties;
};
} // namespace SOUP
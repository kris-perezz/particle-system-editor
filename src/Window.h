#pragma once

#include <src/SOUP_pch.h>

namespace SOUP {
  struct WindowProperties {
    std::string title;
    int width;
    int height;
    bool vsync;
    bool fullscreen;

    WindowProperties(const std::string title = "Particle System Editor",
                     int width          = 1280,
                     int height         = 720,
                     bool vsync              = false,
                     bool fullscreen         = false) {
      this->title      = title;
      this->width      = width;
      this->height     = height;
      this->vsync      = vsync;
      this->fullscreen = fullscreen;
    };
  };

  class Window {
  public:
    Window(const WindowProperties &properties);

    ~Window();

    void onUpdate();

    int getWidth();
    int getHeight();

    bool isVsyncOn();

    void setVsync(bool on);

    SDL_Window *getSDLWindow();
    SDL_GLContext getContext() const;

  private:
    void init(const WindowProperties &properties);

    void shutdown();
    SDL_Window *m_window;
    SDL_GLContext m_context;

    WindowProperties m_windowProperties;
  };
} // namespace SOUP
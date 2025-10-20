#pragma once

#include "glm/fwd.hpp"
#include <src/Events/Event.h>
#include <src/Events/Events.h>
#include <src/SOUP_pch.h>

namespace SOUP {
  struct WindowProperties {
    std::string title;
    int width;
    int height;
    bool vsync;
    bool fullscreen;

    WindowProperties(const std::string title = "Particle System Editor",
                     int width               = 1280,
                     int height              = 720,
                     bool vsync              = false,
                     bool fullscreen         = false) {
      this->title      = title;
      this->width      = width;
      this->height     = height;
      this->vsync      = vsync;
      this->fullscreen = fullscreen;
    };
  };

  class Window : public EventListener {
  public:
    Window(const WindowProperties &properties);

    ~Window();

    bool onEvent(const Event &event) override;
    int getPriority() const override;

    void onUpdate();

    int getWidth();
    int getHeight();
    glm::vec2 getPixelDimensions();

    bool isVsyncOn();

    void setVsync(bool on);

    SDL_Window *getSDLWindow();
    SDL_GLContext getContext() const;

  private:
    void init(const WindowProperties &properties);

    bool onWindowResize(const Event &event);

    void shutdown();
    SDL_Window *m_window;
    SDL_GLContext m_context;

    WindowProperties m_windowProperties;
  };
} // namespace SOUP
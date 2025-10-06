#pragma once

#include <src/SOUP_pch.h>

#include <src/Events/Event.h>
#include <src/Events/Events.h>
#include <src/Events/EventBuffer.h>

#include <src/Layers/Layer.h>
#include <src/Layers/LayerList.h>
#include <src/Window.h>

namespace SOUP {
  class Application {
  public:
    Application();
    ~Application();

    void run();

    bool onEvent(const Event &event);
    void onUpdate(float deltaTime);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

  private:
    LayerList m_layerList;
    EventsDispatcher m_eventsDispatcher;
    EventBuffer m_eventBuffer{512};

    std::unique_ptr<Window> m_window;

    bool m_isRunning = true;
    float m_previousTime = 0.0f;
  };
  
  Application *CreateApplication();
} // namespace SOUP

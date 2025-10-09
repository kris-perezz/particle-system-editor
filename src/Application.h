#pragma once

#include "Inputs/InputSystem.h"
#include <src/SOUP_pch.h>

#include <src/Events/Event.h>
#include <src/Events/EventBuffer.h>
#include <src/Events/Events.h>

#include <src/Layers/Layer.h>
#include <src/Layers/LayerList.h>
#include <src/Window.h>
#include <src/GUI.h>

namespace SOUP {
  class Application : public EventListener {
  public:
    Application() ;
    ~Application();

    void run();

    bool onEvent(const Event &event) override;
    int getPriority() const  override;
    void onUpdate(DeltaTime deltaTime);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

    static Application &get();
    Window &getWindow();

  private:
    LayerList m_layerList;
    EventsDispatcher m_eventsDispatcher;
    EventBuffer m_eventBuffer{512};

    std::unique_ptr<Window> m_window;

    bool m_isRunning = true;

    float m_previousTime = 0.0f;

    static Application *s_Instance;

    GUI *m_GUI = nullptr;

    InputSystem m_input;
  };

  Application *CreateApplication();
} // namespace SOUP

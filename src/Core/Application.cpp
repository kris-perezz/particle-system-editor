#include "imgui_impl_sdl3.h"
#include <src/Core/Application.h>
#include <src/Core/DeltaTime.h>
#include <src/Core/EngineTime.h>
#include <src/Editor/ParticleTestLayer.h>
#include <src/Editor/TestLayer.h>
#include <src/Events/Event.h>
#include <src/Events/EventBuffer.h>
#include <src/Inputs/Input.h>
#include <src/Inputs/InputSystem.h>
#include <src/Layers/Layer.h>
#include <src/Layers/LayerList.h>
#include <src/Particles/ParticleSystem.h>
#include <src/Renderer/RenderCommand.h>

namespace SOUP {

  Application *Application::s_Instance = nullptr;

  Application::Application() {
    s_Instance = this;

    Log::init();
    LOG_TRACE("Logger works?");

    m_eventsDispatcher.registerListener(this);

    WindowProperties properties = {};

    m_window = std::make_unique<SOUP::Window>(properties);
    m_eventsDispatcher.registerListener(m_window.get());

    RenderCommand::setViewport(m_window->getPixelDimensions().x, m_window->getPixelDimensions().y);

    m_GUI = new GUI;

    pushLayer(m_GUI);
    // pushLayer(new Test());
    pushLayer(new ParticleTestLayer());
  }

  Application::~Application() {}

  void Application::run() {
    LOG_TRACE("Running application");

    while (m_isRunning) {
      float currentTime = EngineTime::getTime();

      DeltaTime dt   = currentTime - m_previousTime;
      m_previousTime = currentTime;

      LOG_TRACE("Current Time {}", currentTime);
      LOG_TRACE("Polling...");

      m_input.begin();
      SDL_Event eventFromSDL;
      while (SDL_PollEvent(&eventFromSDL)) {
        ImGui_ImplSDL3_ProcessEvent(&eventFromSDL);

        Event e = TranslateEvent(eventFromSDL);
        if (e.header.type != EventType::None) {
          m_eventBuffer.enqueue(e);
        }
      }

      LOG_TRACE("Dispatching...");
      while (!m_eventBuffer.isEmpty()) {
        m_eventsDispatcher.dispatch(m_eventBuffer.dequeue());
      }
      LOG_TRACE("Done dispatching");

      m_GUI->begin();

      LOG_TRACE("updating layers...");
      Input::bind(&m_input);
      for (auto &layer : m_layerList) {
        layer->onUpdate(dt);
      }

      for (auto &layer : m_layerList) {
        layer->onGUIRender();
      }

      Input::unbind();

      LOG_TRACE("done updating layers");

      m_GUI->end();

      LOG_TRACE("updating window...");
      m_input.end();
      m_window->onUpdate();
      LOG_TRACE("updated window");
      // for each layer in layer list, render layer
    };
  }

  bool Application::onEvent(const Event &event) {

    if (event.header.category == EventCategory::Application) {
      if (event.header.type == EventType::Quit) {
        m_isRunning = false;
        return true;
      }
    }

    if (event.header.type == EventType::WindowLostFocus) {
      m_input.reset();
    }

    if (event.header.type == EventType::WindowResize) {
      return onWindowResize(event);
    }
    return false;
  }

  int Application::getPriority() const { return 1; }

  void Application::onUpdate(DeltaTime deltaTime) {}

  void Application::pushLayer(Layer *layer) {
    m_layerList.pushLayer(layer);
    m_eventsDispatcher.registerListener(layer);
    layer->onAttach();
  }

  void Application::pushOverlay(Layer *overlay) {
    m_layerList.pushLayer(overlay);
    m_eventsDispatcher.registerListener(overlay);
    overlay->onAttach();
  }

  void Application::popLayer(Layer *layer) {
    m_layerList.popLayer(layer);
    m_eventsDispatcher.unregisterListener(layer);
  }

  void Application::popOverlay(Layer *overlay) {
    m_layerList.popLayer(overlay);
    m_eventsDispatcher.unregisterListener(overlay);
  }

  Application &Application::get() { return *s_Instance; }

  Window &Application::getWindow() { return *m_window; }

  bool Application::onWindowResize(const Event &event) {
    RenderCommand::setViewport(m_window->getPixelDimensions().x, m_window->getPixelDimensions().y);
    return false;
  }

} // namespace SOUP
#include <src/Application.h>
#include <src/DeltaTime.h>
#include <src/EngineTime.h>
#include <src/Events/Event.h>
#include <src/Events/EventBuffer.h>

namespace SOUP {
  Application::Application() {
    Log::init();
    LOG_INFO("Logger works?");

    WindowProperties properties = {};

    m_window = std::make_unique<SOUP::Window>(properties);
  }

  Application::~Application() {}

  void Application::run() {
    LOG_INFO("Running application");

    while (m_isRunning) {
      float currentTime = EngineTime::getTime();

      DeltaTime dt   = currentTime - m_previousTime;
      m_previousTime = currentTime;

      SDL_Event eventFromSDL;
      while (SDL_PollEvent(&eventFromSDL)) {

        Event e = TranslateEvent(eventFromSDL);
        if (e.header.type != EventType::None) {
          m_eventBuffer.enqueue(e);
        }
      }

      while (!m_eventBuffer.isEmpty()) {
        m_eventsDispatcher.dispatch(m_eventBuffer.dequeue());
      }

      for (auto &layer : m_layerList) {
        layer->onUpdate(dt);
      }
      // for each layer in layer list, render layer
    };
  }

  bool Application::onEvent(const Event &event) { return false; }

  void Application::onUpdate(float deltaTime) {}

  void Application::pushLayer(Layer *layer) {}

  void Application::pushOverlay(Layer *overlay) {}

  void Application::popLayer(Layer *layer) {}

  void Application::popOverlay(Layer *overlay) {}

} // namespace SOUP
#include <src/Events/Events.h>

namespace SOUP {
void EventsDispatcher::dispatch(const SDL_Event &event) {
  for (auto &[priority, listeners] : m_listeners) {
    for (auto *listener : listeners) {
      if (listener->onEvent(event))
        return;
    }
  }
}

void EventsDispatcher::poll() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    dispatch(event);
  }
}

void EventsDispatcher::registerListener(int priority, EventListener *listener) {
  m_listeners[priority].push_back(listener);
  LOG_INFO("Event listener with priority {} registered", priority);
}

void EventsDispatcher::unregisterListener(EventListener *listener) {
  for (auto &[priority, vec] : m_listeners) {
    for (auto i = vec.begin(); i != vec.end();) {
      if (*i == listener) {
        i = vec.erase(i);
      } else {
        i++;
      }
    }
  }
  LOG_INFO("Event listener unregistered");
}
} // namespace SOUP
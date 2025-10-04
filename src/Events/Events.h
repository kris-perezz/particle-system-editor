#pragma once

#include <src/SOUP_pch.h>

#include <src/Events/Event.h>

namespace SOUP {
  class EventListener {
  public:
    virtual ~EventListener() = default;

    virtual bool onEvent(Event &event) = 0;
    virtual int getPriority() const    = 0;
  };

  class EventsDispatcher {
  public:
    void dispatch(const Event &event);
    void registerListener(EventListener *newListener);
    void unregisterListener(EventListener *targetListener);

  private:
    struct Listener {
      int priority;
      EventListener *listener_ptr;
    };

    std::vector<Listener> m_listeners;
  };
} // namespace SOUP

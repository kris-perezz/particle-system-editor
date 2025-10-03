#include <src/SOUP_pch.h>

namespace SOUP {
class EventListener {
public:
  virtual bool onEvent(const SDL_Event &event) = 0;
  virtual ~EventListener() = default;
};

class EventsDispatcher {
public:
  void dispatch(const SDL_Event &event);
  void poll();
  void registerListener(int priority, EventListener *listener);
  void unregisterListener(EventListener *listener);

private:
  std::map<int, std::vector<EventListener *>, std::less<int>> m_listeners;
};
} // namespace SOUP

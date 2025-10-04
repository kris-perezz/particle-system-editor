#pragma once

#include <src/SOUP_pch.h>

#include <src/Events/Events.h>

namespace SOUP {
class Layer : public EventListener {
public:
  Layer(const std::string &name);
  virtual ~Layer() = default;

  virtual void onAttach() {}
  virtual void onDetach() {}
  virtual void onUpdate() {}
  virtual bool onEvent(const SDL_Event &event) = 0;

  const std::string &GetName();

protected:

private:
  std::string m_debugName;
};

} // namespace SOUP

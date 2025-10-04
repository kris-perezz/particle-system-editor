#pragma once

#include <src/SOUP_pch.h>

#include <src/Events/Events.h>

namespace SOUP {
  class Layer : public EventListener {
  public:
    Layer(int priority);
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate() {}
    virtual bool onEvent(Event &event) = 0;

    virtual int getPriority() const = 0;

  protected:
  private:
    int m_priority;
  };

} // namespace SOUP

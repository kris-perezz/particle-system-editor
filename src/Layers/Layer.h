#pragma once

#include "DeltaTime.h"
#include <src/SOUP_pch.h>

#include <src/Events/Events.h>

namespace SOUP {
  class Layer : public EventListener {
  public:
    Layer(int priority);
    virtual ~Layer() = default;

    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void onUpdate(DeltaTime deltaTime) {}
    virtual bool onEvent(const Event &event) = 0;

    virtual void onGUIRender() {}

    int getPriority() const;

  protected:
  private:
    int m_priority;
  };

} // namespace SOUP
